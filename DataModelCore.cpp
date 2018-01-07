#include "DataModelCore.h"
#include <QDir>
#include <QFileInfo>
#include <QMap>
#include <QProcess>

DataModelCore::DataModelCore(QObject *parent) : QAbstractListModel(parent)
{
    updateDbInfo();
}

QStringList DataModelCore::getPlaneTypes()
{
    QStringList planeTypeList ;
    for(SceneFileProp sceneProp:_sceneMap)
    {
        if (!planeTypeList.contains(sceneProp.mSceneType, Qt::CaseInsensitive))
            planeTypeList.append(sceneProp.mSceneType);
    }
    return planeTypeList;
}

QStringList DataModelCore::getFlightPhases()
{
    QStringList flightPhaseList ;
    for(SceneFileProp sceneProp:_sceneMap)
    {
        if (!flightPhaseList.contains(sceneProp.mScenePhase, Qt::CaseInsensitive))
            flightPhaseList.append(sceneProp.mScenePhase);
    }
    return flightPhaseList;
}

QStringList DataModelCore::getTaskDif()
{
    QStringList tskList ;
    for(SceneFileProp sceneProp:_sceneMap)
    {
        if (!tskList.contains(sceneProp.mSceneTsk, Qt::CaseInsensitive))
            tskList.append(sceneProp.mSceneTsk);
    }
    return tskList;
}

void DataModelCore::getSceneList()
{
    beginResetModel();
    _resultList.clear();
    for(SceneFileProp sceneProp:_sceneMap)
    {
        _resultList.append(sceneProp);
    }
    endResetModel();
}

void DataModelCore::getMatchKey(QString val)
{
    beginResetModel();
    _resultList.clear();
    for(SceneFileProp sceneProp:_sceneMap)
    {
        if (sceneProp.mSceneType.contains(val)||
                sceneProp.mScenePhase.contains(val)||
                sceneProp.mSceneTsk.contains(val)||
                sceneProp.mSceneName.contains(val))
            _resultList.append(sceneProp);
    }
    endResetModel();
}

void DataModelCore::getClassList(QString planeType, QString flightPhase, QString taskDif)
{
    beginResetModel();
    _resultList.clear();
    for(SceneFileProp sceneProp:_sceneMap)
    {
        if (sceneProp.mSceneType.contains(planeType)&&
                sceneProp.mScenePhase.contains(flightPhase)&&
                sceneProp.mSceneTsk.contains(taskDif))
            _resultList.append(sceneProp);
    }
    endResetModel();
}

bool DataModelCore::updateDbInfo()
{
    clearUp();
    QMap<QString, QObject*> tempDb;
    QDir dir = QDir("Data");
    if (!dir.exists())
        return false;
    dir.setFilter(QDir::Files);
    QFileInfoList infoList = dir.entryInfoList();
    QString sceneType, scenePhase, sceneTsk, sceneName, seceClass;
    foreach(QFileInfo fileInfo, infoList)
    {
        QString fullName = fileInfo.completeBaseName();
        QStringList fileProp = fullName.split('-');
        if (fileProp.count() != 5)
            continue;
        sceneType = fileProp.at(0);
        scenePhase = fileProp.at(1);
        sceneTsk = fileProp.at(2);
        sceneName = fileProp.at(3);
        seceClass = fileProp.at(4);
        SceneFileProp sceneProp = _sceneMap[sceneName];
        sceneProp.mSceneType = sceneType;
        sceneProp.mScenePhase = scenePhase;
        sceneProp.mSceneTsk = sceneTsk;
        sceneProp.mSceneName = sceneName;
        if (seceClass.contains("简介"))
        {
            QFile file(fileInfo.absoluteFilePath());
            file.open(QIODevice::ReadOnly);
            sceneProp.mSceneAbs = QString::fromLocal8Bit(file.readAll());
        }
        else if (seceClass.contains("需求"))
        {
            sceneProp.mSceneReqPath = fileInfo.fileName();
        }
        else if (seceClass.contains("流程"))
        {
            sceneProp.mSceneFlowPath = fileInfo.fileName();
        }
        else if (seceClass.contains("结果"))
        {
            sceneProp.mSceneResultPath = fileInfo.fileName();
        }
        _sceneMap[sceneName] = sceneProp;
    }

    return true;
}

void DataModelCore::openSpeFile(int row, int col)
{
    if (_resultList.count() <= row||
            row<0||
            col<2||
            col >=5)
        return ;
   SceneFileProp sceneProp = _resultList[row];
   QDir dir = QDir("Data");
   QString appCmd = "";
   if (col == 2)
       appCmd = sceneProp.mSceneReqPath;
   else if (col == 3)
       appCmd = sceneProp.mSceneFlowPath;
   else
       appCmd = sceneProp.mSceneResultPath;
   QString cmd = dir.absoluteFilePath(appCmd);
   QByteArray rawData = cmd.toLocal8Bit();
   system(rawData.data());
}

int DataModelCore::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _resultList.count();
}

//int DataModelCore::columnCount(const QModelIndex &parent) const
//{
//    Q_UNUSED(parent)
//    return 5;
//}

QVariant DataModelCore::data(const QModelIndex &index, int role) const
{
    if (index.row() >= rowCount()||
            index.row() < 0)
        return QVariant();
    SceneFileProp sceneProp = _resultList.at(index.row());
    if (role == SceneNameRole)
        return sceneProp.mSceneName;
    else if (role == SceneAbsRole)
        return sceneProp.mSceneAbs;
    else if (role == SceneReqRole)
        return sceneProp.mSceneReqPath;
    else if (role == SceneFlowRole)
        return sceneProp.mSceneFlowPath;
    else if (role == SceneResultRole)
        return sceneProp.mSceneResultPath;
    else
        return QVariant();
}

QHash<int, QByteArray> DataModelCore::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[SceneNameRole] = "sceneName";
    roles[SceneAbsRole] = "sceneAbs";
    roles[SceneReqRole] = "sceneReq";
    roles[SceneFlowRole] = "sceneFlow";
    roles[SceneResultRole] = "sceneResult";
    return roles;
}

void DataModelCore::clearUp()
{
    _planeTypes.clear();
    _flightPhases.clear();
    _taskDifs.clear();
    for(QObject* model: _db)
    {

        delete (HmiDbModel*)model;
        model = 0;
    }
    _db.clear();
}
