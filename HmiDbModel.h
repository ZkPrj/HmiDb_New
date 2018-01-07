#ifndef HMIDBMODEL_H
#define HMIDBMODEL_H

#include <QObject>

class HmiDbModel : public QObject
{
    Q_OBJECT
public:
    explicit HmiDbModel(QString name = "", QString abs = "", QString req = "", QString flow = "", QString result = "", QObject *parent = 0);
    Q_PROPERTY(QString sceneName READ sceneName)
    Q_PROPERTY(QString sceneAbs READ sceneAbs)
    Q_PROPERTY(QString sceneReq READ sceneReq)
    Q_PROPERTY(QString sceneFlow READ sceneFlow)
    Q_PROPERTY(QString sceneResult READ sceneResult)

    QString sceneName();
    QString sceneAbs();
    QString sceneReq();
    QString sceneFlow();
    QString sceneResult();
    void setSceneName(QString str);
    void setSceneAbs(QString str);
    void setSceneReq(QString str);
    void setSceneFlow(QString str);
    void setSceneResult(QString str);
signals:

public slots:

private:
    QString _sceneName;
    QString _sceneAbs;
    QString _sceneReq;
    QString _sceneFlow;
    QString _sceneResult;
};

#endif // HMIDBMODEL_H
