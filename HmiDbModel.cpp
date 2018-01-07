#include "HmiDbModel.h"

HmiDbModel::HmiDbModel(QString name, QString abs, QString req, QString flow, QString result, QObject *parent):
    _sceneName(name), _sceneAbs(abs), _sceneReq(req), _sceneFlow(flow), _sceneResult(result)
{
}

QString HmiDbModel::sceneName()
{
    return _sceneName;
}

QString HmiDbModel::sceneAbs()
{
    return _sceneAbs;
}

QString HmiDbModel::sceneReq()
{
    return _sceneReq;
}

QString HmiDbModel::sceneFlow()
{
    return _sceneFlow;
}

QString HmiDbModel::sceneResult()
{
    return _sceneResult;
}

void HmiDbModel::setSceneName(QString str)
{
    _sceneName = str;
}

void HmiDbModel::setSceneAbs(QString str)
{
    _sceneAbs = str;
}

void HmiDbModel::setSceneReq(QString str)
{
    _sceneReq = str;
}

void HmiDbModel::setSceneFlow(QString str)
{
    _sceneFlow = str;
}

void HmiDbModel::setSceneResult(QString str)
{
    _sceneResult = str;
}
