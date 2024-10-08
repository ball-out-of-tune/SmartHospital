#ifndef SQLITEOPERATOR_H
#define SQLITEOPERATOR_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <string>

class SqliteOperator
{
public:
    SqliteOperator();
    //
    bool connect(const QString &dbName);

    // 打开数据库
    bool openDb(void);
    // 创建数据表
    bool createTable(void);
    // 判断数据表是否存在
    bool isTableExist(QString& tableName);
    //whether username matches password
    bool validateLogin(QString username, QString InputPassword);

    // 查询全部数据
    void queryTable();
    // 插入数据
    bool singleInsertData(QVariant userName, QVariant Password); // 插入单条数据
    void moreInsertData(); // 插入多条数据
    // 修改数据
    void modifyData(int id, QString name, int age);
    // 删除数据
    void deleteData(int id);
    //删除数据表
    void deleteTable(QString& tableName);
    // 关闭数据库
    void closeDb(void);

private:
    // 用于建立和数据库的连接
    QSqlDatabase database;
    //the account database to be establish
    QSqlDatabase accountDb;
};


#endif // SQLITEOPERATOR_H
