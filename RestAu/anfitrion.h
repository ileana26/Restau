#ifndef ANFITRION_H
#define ANFITRION_H

#include <QWidget>
#include <QString>
#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <qdebug.h>

namespace Ui {
class Anfitrion;
}

class Anfitrion : public QWidget
{
    Q_OBJECT

public:
    explicit Anfitrion(int id,QWidget *parent = nullptr);
    ~Anfitrion();

private slots:
    void on_Dipinibilidad_Mesas_clicked();

    void on_Disponibilidad_Mesas_clicked();

    void on_salida_clicked();

    void on_Mesa_1_clicked();

    void on_Mesa_2_clicked();

    void on_Mesa_3_clicked();

    void on_Mesa_4_clicked();

private:
    Ui::Anfitrion *ui;
    QSqlDatabase  conexion;
    QString id;
};

#endif // ANFITRION_H
