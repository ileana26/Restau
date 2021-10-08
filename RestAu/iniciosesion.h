#ifndef INICIOSESION_H
#define INICIOSESION_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <qdebug.h>
#include "gerente.h"
#include "anfitrion.h"
#include "mesero.h"
#include "cocinero.h"

QT_BEGIN_NAMESPACE
namespace Ui { class InicioSesion; }
QT_END_NAMESPACE

class InicioSesion : public QMainWindow
{
    Q_OBJECT

public:
    InicioSesion(QWidget *parent = nullptr);
    ~InicioSesion();

private slots:
    void on_pushButton_clicked();

private:
    Ui::InicioSesion *ui;
    QSqlDatabase  conexion;
};
#endif // INICIOSESION_H
