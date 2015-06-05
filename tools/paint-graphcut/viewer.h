#ifndef VIEWER_H
#define VIEWER_H

#include <QGLViewer/qglviewer.h>
#include <QGLViewer/vec.h>
using namespace qglviewer;

#include "curvegroup.h"

class Viewer : public QGLViewer
{
  Q_OBJECT

 public :
  Viewer(QWidget *parent=0);

  void init();
  void draw();

  void setGridSize(int, int, int);
  void setMultiMapCurves(int, QMultiMap<int, Curve*>*);
  void setListMapCurves(int, QList< QMap<int, Curve> >*);

  void setVolDataPtr(uchar*);
  void setMaskDataPtr(uchar*);

  void keyPressEvent(QKeyEvent*);

  public slots :
    void setPointSize(int p) { m_pointSize = p; update(); }
    void setVoxelInterval(int p) { m_pointSkip = p; }
    void updateVoxels();
    void updateViewerBox(int, int, int, int, int, int);
    void updateCurrSlice(int, int);
    void setVoxelChoice(int p) { m_voxChoice = p; }
    void setShowBox(bool);
    void saveImage() { saveSnapshot(false); };
    void setPaintedTags(QList<int>);
    void setCurveTags(QList<int>);

 private :
  int m_depth, m_width, m_height;
  int m_minDSlice, m_maxDSlice;
  int m_minWSlice, m_maxWSlice;
  int m_minHSlice, m_maxHSlice;

  int m_voxChoice;
  bool m_showBox;

  uchar *m_volPtr;
  uchar *m_maskPtr;
  int m_pointSkip;
  int m_pointSize;

  int m_currSlice, m_currSliceType;

  QMultiMap<int, Curve*> *m_Dcg;
  QMultiMap<int, Curve*> *m_Wcg;
  QMultiMap<int, Curve*> *m_Hcg;
  QList< QMap<int, Curve> > *m_Dmcg;  
  QList< QMap<int, Curve> > *m_Wmcg;  
  QList< QMap<int, Curve> > *m_Hmcg;  

  QList<ushort> m_voxels;

  QList<int> m_paintedTags;
  QList<int> m_curveTags;


  void drawBox();
  
  void drawMMDCurve();
  void drawMMWCurve();
  void drawMMHCurve();

  void drawLMDCurve();
  void drawLMWCurve();
  void drawLMHCurve();

  void drawVolMask();
  void drawVol();

  void updateVoxelsWithTF();

  void drawEnclosingCube(Vec, Vec);
  void drawCurrentSlice(Vec, Vec);

};

#endif