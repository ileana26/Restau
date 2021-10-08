#ifndef COCINERO_H
#define COCINERO_H

#include <QWidget>
#include <QString>
#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <qdebug.h>
#include <qdebug.h>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

namespace Ui {
class cocinero;
}

class cocinero : public QWidget
{
    Q_OBJECT

public:
    explicit cocinero(int id,QWidget *parent = nullptr);
    ~cocinero();

private slots:
    void on_Ordenes_Mesas_clicked();

    void on_salida_clicked();

    void on_Mesa_1_clicked();

    void on_Mesa_2_clicked();

    void on_Mesa_3_clicked();

    void on_BotonTerminado_clicked();

private:
    Ui::cocinero *ui;
    QSqlDatabase  conexion;
    QString id;
    QString NuMes;
    int NumeMesa;
};

#endif // COCINERO_H
