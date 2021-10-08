#include "cocinero.h"
#include "ui_cocinero.h"
#include "iniciosesion.h"
#include "QStandardItemModel"
#include "QPrintDialog"
#include <QPrinter>
#include <string>
#include "string"
#include "QPrintDialog"
#include <QPdfWriter>
#include <QTextDocument>
#include <QDesktopServices>
#include <QPainter>

cocinero::cocinero(int id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cocinero)
{
    this->id=id;
    this->id.toUInt();
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    ui->ordenMesa->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->ordenMesa->setDragEnabled(true);
    ui->ordenMesa->setDragDropMode(QAbstractItemView::DragDrop);
    ui->ordenMesa->viewport()->setAcceptDrops(false);
    ui->ordenMesa->setDropIndicatorShown(true);

    //Query para conocer el estatus de la orden
    /*
    QSqlQuery estatus;
    QString estat = "En proceso";
    QString Est;

    estatus.prepare("select estatus from orden where mesa_idMesa = 1");
    estatus.exec();

    if(estatus.next()){
        Est = estatus.value(0).toString();
    }

    if(Est == estat){
        ui->Mesa_1->setStyleSheet("QPushButton { background-color: #FF7F00; } ");
        ui->Mesa_2->setStyleSheet("QPushButton { background-color: #FF7F00; } ");
        ui->Mesa_3->setStyleSheet("QPushButton { background-color: #FF7F00; } ");
    }
    */
}

cocinero::~cocinero()
{
    delete ui;
}

void cocinero::on_Ordenes_Mesas_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void cocinero::on_salida_clicked()
{
    close();
    InicioSesion *regresa= new InicioSesion();
    regresa->show();
}


void cocinero::on_Mesa_1_clicked()
{
    ui->Mesa_1->setStyleSheet("QPushButton { background-color: #FF7F00; } ");
    conexion.open();
    QSqlQuery Orden;
    ui->ordenMesa->clear();
    QString mesa ="Mesa 1: \n";
    QListWidgetItem * menu = new QListWidgetItem;
    menu->setText(mesa);
    ui->ordenMesa->addItem(mesa);

    Orden.prepare("select nombre from comida inner join orden on orden.idComida=comida.idComida and orden.mesa_idMesa=1 where orden.estatus='En proceso.' ");
    Orden.exec();
    while(Orden.next()){
        QString orden=Orden.value(0).toString();
            QString datos =orden+"\n";
            QListWidgetItem * menu = new QListWidgetItem;
            menu->setText(datos);
            ui->ordenMesa->addItem(datos);
    }
}


void cocinero::on_Mesa_2_clicked()
{
    ui->Mesa_2->setStyleSheet("QPushButton { background-color: #FF7F00; } ");
    conexion.open();
    QSqlQuery Orden;
    ui->ordenMesa->clear();
    QString mesa ="Mesa 2: \n";
    QListWidgetItem * menu = new QListWidgetItem;
    menu->setText(mesa);
    ui->ordenMesa->addItem(mesa);

    Orden.prepare("select nombre from comida inner join orden on orden.idComida=comida.idComida and orden.mesa_idMesa=2 where orden.estatus='En proceso.' ");
    Orden.exec();
    while(Orden.next()){
        QString orden=Orden.value(0).toString();
            QString datos =orden+"\n";
            QListWidgetItem * menu = new QListWidgetItem;
            menu->setText(datos);
            ui->ordenMesa->addItem(datos);
    }
}

void cocinero::on_Mesa_3_clicked()
{
    ui->Mesa_3->setStyleSheet("QPushButton { background-color: #FF7F00; } ");
    conexion.open();
    QSqlQuery Orden;
    ui->ordenMesa->clear();
    QString mesa ="Mesa 3: \n";
    QListWidgetItem * menu = new QListWidgetItem;
    menu->setText(mesa);
    ui->ordenMesa->addItem(mesa);

    Orden.prepare("select nombre from comida inner join orden on orden.idComida=comida.idComida and orden.mesa_idMesa=3 where orden.estatus='En proceso.'");
    Orden.exec();
    while(Orden.next()){
        QString orden=Orden.value(0).toString();
            QString datos =orden+"\n";
            QListWidgetItem * menu = new QListWidgetItem;
            menu->setText(datos);
            ui->ordenMesa->addItem(datos);
    }
}

void cocinero::on_BotonTerminado_clicked()
{
    int Mes1 = 1;
    int Mes2 = 2;
    int Mes3 = 3;

    NuMes = ui->NumeroMesa->value();
    conexion.open();

    QMessageBox msj1;
    msj1.setText("¿Finalizar pedido?");
    QAbstractButton * Ac = msj1.addButton("Aceptar",QMessageBox::AcceptRole);
    QAbstractButton * Denied = msj1.addButton("Cancelar",QMessageBox::NoRole);
    msj1.setIcon(QMessageBox::Information);

    msj1.exec();

    if(msj1.clickedButton() == Ac){

    if(NuMes == Mes1){
        ui->Mesa_1->setStyleSheet("QPushButton { background-color: #39be00; }");
        qDebug() << NuMes;
        QSqlQuery finish;
        finish.prepare("update orden set estatus = 'Finalizada.' where mesa_idMesa = 1 ");
        finish.exec();
        finish.next();
    }

    if(NuMes == Mes2){
        ui->Mesa_2->setStyleSheet("QPushButton { background-color: #39be00; }");
        qDebug() << NuMes;
        QSqlQuery finish2;
        finish2.prepare("update orden set estatus = 'Finalizada.' where mesa_idMesa = 2 ");
        finish2.exec();
      finish2.next();
    }

    if(NuMes == Mes3){
        ui->Mesa_3->setStyleSheet("QPushButton { background-color: #39be00; }");
        qDebug() << NuMes;
        QSqlQuery finish3;
        finish3.prepare("update orden set estatus = 'Finalizada.' where mesa_idMesa = 3 ");
        finish3.exec();
        finish3.next();
    }
    }
}
