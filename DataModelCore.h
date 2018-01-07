#ifndef DATAMODELCORE_H
#define DATAMODELCORE_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QAbstractListModel>

#include "HmiDbModel.h"

struct SceneFileProp
{
    QString mSceneType; /*场景机型*/
    QString mScenePhase;    /*场景飞行阶段*/
    QString mSceneTsk;      /*场景任务难度*/
    QString mSceneName; /*场景名称*/
    QString mSceneAbs;  /*场景简介*/
    QString mSceneReqPath;  /*场景需求名*/
    QString mSceneFlowPath; /*场景流程名*/
    QString mSceneResultPath;    /*场景结果名*/
};

class DataModelCore : public QAbstractListModel
{
    Q_OBJECT
public: /*QML中直接使用的接口*/
    explicit DataModelCore(QObject *parent = 0);
    Q_INVOKABLE QStringList getPlaneTypes();
    Q_INVOKABLE QStringList getFlightPhases();
    Q_INVOKABLE QStringList getTaskDif();
    Q_INVOKABLE void getSceneList();
    Q_INVOKABLE void getMatchKey(QString val);
    Q_INVOKABLE void getClassList(QString planeType, QString flightPhase, QString taskDif);
    Q_INVOKABLE bool updateDbInfo();
    Q_INVOKABLE void openSpeFile(int row, int col);


public:/*List Model 的接口*/
    enum AnimalRoles {
        SceneNameRole = Qt::UserRole + 1,
        SceneAbsRole,
        SceneReqRole,
        SceneFlowRole,
        SceneResultRole,
    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    //int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index = QModelIndex(), int role = Qt::DisplayRole) const;
protected:
    QHash<int, QByteArray> roleNames()const;


private:
    void clearUp();
signals:

public slots:

private:
    QStringList _planeTypes;
    QStringList _flightPhases;
    QStringList _taskDifs;
    QList<QObject*> _db;
    QList<SceneFileProp> _resultList;
    QMap<QString, SceneFileProp> _sceneMap;
};

#endif // DATAMODELCORE_H
