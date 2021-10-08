#include "gerente.h"
#include "ui_gerente.h"
#include "iniciosesion.h"
#include "QPrintDialog"
#include <QPrinter>
#include <QPdfWriter>
#include <QTextDocument>
#include <QDesktopServices>

gerente::gerente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gerente)
{
    ui->setupUi(this);

    QStringList titulos;
    QStringList inventario;
        ui->tableusuario->setColumnCount(6);
        ui->inventario_Tabla->setColumnCount(5);
        titulos<< "Id" << "Nombre" <<"Apellido Paterno" << "Apellido Materno" << "Puesto"<<"Edad";
        inventario<<"Estado"<<"Restantes"<<"Nombre"<<"Tipo"<<"Id";
        ui->tableusuario->setHorizontalHeaderLabels(titulos);
        ui->inventario_Tabla->setHorizontalHeaderLabels(inventario);
        ui->tableusuario->setColumnCount(6);

        QSqlQuery MatAtra;
        MatAtra.prepare("select * from usuario");
        MatAtra.exec();
        while(MatAtra.next()){

                QString idusu=MatAtra.value(0).toString();
                QString nombre=MatAtra.value(1).toString();
                QString apellidom=MatAtra.value(2).toString();
                QString Apellidop=MatAtra.value(3).toString();
                QString puesto=MatAtra.value(4).toString();
                QString edad=MatAtra.value(6).toString();

                ui->tableusuario->insertRow(ui->tableusuario->rowCount());

                ui->tableusuario->setItem(ui->tableusuario->rowCount()-1,0,new QTableWidgetItem(idusu));
                ui->tableusuario->setItem(ui->tableusuario->rowCount()-1,1,new QTableWidgetItem(nombre));
                ui->tableusuario->setItem(ui->tableusuario->rowCount()-1,2,new QTableWidgetItem(apellidom));
                ui->tableusuario->setItem(ui->tableusuario->rowCount()-1,3,new QTableWidgetItem(Apellidop));
                ui->tableusuario->setItem(ui->tableusuario->rowCount()-1,4,new QTableWidgetItem(puesto));
                ui->tableusuario->setItem(ui->tableusuario->rowCount()-1,5,new QTableWidgetItem(edad));
    }
}

gerente::~gerente()
{
    delete ui;
}


void gerente::on_lineEdit_textChanged(const QString &arg1)
{
    ui->tableusuario->setRowCount(0);
        ui->tableusuario->setColumnCount(0);

        QStringList titulos;
        ui->tableusuario->setColumnCount(6);
        titulos<< "ID" << "Nombre" <<"Apellido Paterno" << "Apellido Materno" << "Puesto" << "Edad";
        ui->tableusuario->setHorizontalHeaderLabels(titulos);

        QSqlQuery Buscar;
        Buscar.prepare("select * from usuario where idUsuario like '%"+arg1+"%'");
        Buscar.exec();
        while(Buscar.next()){
            QString idusu=Buscar.value(0).toString();
            QString nombre=Buscar.value(1).toString();
            QString apellidom=Buscar.value(2).toString();
            QString Apellidop=Buscar.value(3).toString();
            QString puesto=Buscar.value(4).toString();
            QString edad=Buscar.value(6).toString();

            ui->tableusuario->insertRow(ui->tableusuario->rowCount());

            ui->tableusuario->setItem(ui->tableusuario->rowCount()-1,0,new QTableWidgetItem(idusu));
            ui->tableusuario->setItem(ui->tableusuario->rowCount()-1,1,new QTableWidgetItem(nombre));
            ui->tableusuario->setItem(ui->tableusuario->rowCount()-1,2,new QTableWidgetItem(apellidom));
            ui->tableusuario->setItem(ui->tableusuario->rowCount()-1,3,new QTableWidgetItem(Apellidop));
            ui->tableusuario->setItem(ui->tableusuario->rowCount()-1,4,new QTableWidgetItem(puesto));
            ui->tableusuario->setItem(ui->tableusuario->rowCount()-1,5,new QTableWidgetItem(edad));

}
}

void gerente::on_pushButton_clicked()
{
    close();
    InicioSesion *regresa= new InicioSesion();
    regresa->show();
}

void gerente::on_Buscar_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}


void gerente::on_Agregar_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

void gerente::on_agregarusuario_clicked()
{
    QString nom = ui->nombreusuario->text();
    QString ap = ui->apellidop->text();
    QString am = ui->apellidom->text();
    QString ed= ui->edad->text();
    QString pue= ui->puestousuario->currentText();
    QString contrasenia = "123";
    QMessageBox msg;

    //agregar datos
    if(nom.length()>0 && ap.length()>0 && am.length()>0 &&  ed.length()>0 && pue.length()>0)
       {
                 msg.setWindowTitle("Datos Correctos");
                 msg.setIcon(QMessageBox::Question);
                 msg.setText("¿Estas seguro de agregar un nuevo usuario?");
                 QAbstractButton * pButtonYes = msg.addButton(tr("SI"),QMessageBox::YesRole);
                 msg.addButton(tr("NO"),QMessageBox::NoRole);
                 msg.exec();
                 if(msg.clickedButton()==pButtonYes){

       QSqlQuery anfi;
       QSqlQuery cocine;
       QSqlQuery mese;
       QSqlQuery geren;


        if(pue == "Gerente"){

            geren.prepare("call InsertarGerente('"+nom+"','"+ap+"','"+am+"','"+ed+"','"+contrasenia+"')");
            geren.exec();
        }
        if(pue == "Cocinero"){

            cocine.prepare("call InsertarCocinero('"+nom+"','"+ap+"','"+am+"','"+ed+"','"+contrasenia+"')");
            cocine.exec();
        }
        if(pue == "Mesero"){

            mese.prepare("call InsertarMesero('"+nom+"','"+ap+"','"+am+"','"+ed+"','"+contrasenia+"')");
            mese.exec();
        }
        if(pue == "Anfitrion"){

            anfi.prepare("call InsertarAnfitrion('"+nom+"','"+ap+"','"+am+"','"+ed+"','"+contrasenia+"')");
            anfi.exec();
        }

            QMessageBox msg1;
            msg.setWindowTitle("Exito");
               msg1.setIcon(QMessageBox::Information);
               msg1.setText("El usuario ha sido registrado");
               msg.addButton(tr("Aceptar"),QMessageBox::YesRole);
               msg1.exec();
                 }
    }
    else
    {
        msg.setWindowTitle("Campos vacios");
               msg.setIcon(QMessageBox::Warning);
               msg.setText("Por favor rellene todos los campos");
               msg.addButton(tr("Aceptar"),QMessageBox::YesRole);
               msg.exec();
    }

}


void gerente::on_Editar_clicked()
{

    if(ui->lineEdit->text() == ""){
        QMessageBox::critical(this,"Error","Inserte un ID.","Aceptar");
        return;
    }
    else
    {
      ui->stackedWidget_2->setCurrentIndex(1);

    //MOSTRAR DATOS EN LABLES

    bool busqueda;
    QMessageBox msg;
    QSqlQuery mostrar;
    QString id = ui->lineEdit->text();

    if(id.length()>0)
    {
    mostrar.prepare("Select nombre,ApellidoPaterno,ApellidoMaterno,puesto,edad FROM USUARIO WHERE idUsuario = '"+id+"';");
    mostrar.exec();
    while(mostrar.next())
    {
    QString nombre1 = mostrar.value(0).toString();
    QString ape= mostrar.value(1).toString();
    QString apem = mostrar.value(2).toString();
    QString ed = mostrar.value(4).toString();
    QString pues = mostrar.value(3).toString();

    ui->nomusuario->setText(nombre1);
    ui->apepaterno->setText(ape);
    ui->apematerno->setText(apem);
    ui->edadusuario->setText(ed);
    ui->puestou->setCurrentText(pues);
    busqueda =1;
    }
    if(busqueda == 0)
    {
        msg.setWindowTitle("Error busqueda");
               msg.setIcon(QMessageBox::Critical);
               msg.setText("El usuario ingresado no se encuentra en el sistema");
               msg.addButton(tr("Aceptar"),QMessageBox::YesRole);
               msg.exec();
    }


    }
    }
}

void gerente::on_Guardarcambios_clicked()
{

    QString id=ui->lineEdit->text();
    QString nombrenuevo=ui->nomusuario->text();
    QString apnuevo=ui->apepaterno->text();
    QString amnuevo=ui->apematerno->text();
    QString ednuevo=ui->edadusuario->text();
    QString puestonuevo = ui->puestou->currentText();

        //Cambiar contraseña
    QString contra=ui->contrasenia1->text();
    QString contra2=ui->contrasenia2->text();

    QSqlQuery actualizar;

if(contra=="" && contra2 =="")
{
    QMessageBox::information(this, "Error", "Ingrese una contraseña", "Aceptar");

}
     if(contra==contra2){
         QMessageBox msg;
         msg.setWindowTitle("Confirmación");
          msg.setIcon(QMessageBox::Question);
          msg.setText("Seguro de guardar cambios");
          QAbstractButton * pButtonYes = msg.addButton(tr("SI"),QMessageBox::YesRole);
          msg.addButton(tr("NO"),QMessageBox::NoRole);
          msg.exec();

          if(msg.clickedButton()==pButtonYes){

            qDebug() << "si entra";
              actualizar.prepare("UPDATE USUARIO SET password='"+contra+"', nombre='"+nombrenuevo+"', ApellidoPaterno='"+apnuevo+"' , ApellidoMaterno='"+amnuevo+"' , edad='"+ednuevo+"' , puesto='"+puestonuevo+"' where idUsuario= '"+id+"'");
              actualizar.exec();
              QMessageBox::information(this, "Aviso", "Datos actualizados", "Aceptar");
              }

             }
     else {
            QMessageBox msg;
            msg.setWindowTitle("Datos incorrectos");
             msg.setIcon(QMessageBox::Critical);
             msg.setText("Las contraseñas no coinciden");
             msg.addButton(tr("VOLVER"),QMessageBox::YesRole);
             msg.exec();
     }
}

void gerente::on_vercontra_stateChanged(int arg1)
{
    ui->contrasenia1->setEchoMode(ui->vercontra->checkState() == Qt::Checked ? QLineEdit::Normal : QLineEdit::Password);
    ui->contrasenia2->setEchoMode(ui->vercontra->checkState() == Qt::Checked ? QLineEdit::Normal : QLineEdit::Password);
}

void gerente::on_Inventario_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
}

void gerente::on_pushButton_2_clicked()
{
    ui->inventario_Tabla->setRowCount(0);
        QSqlQuery desayunos;
        desayunos.prepare("SELECT idComida,tipo,nombre,raciones from comida where tipo='Desayunos'");
        desayunos.exec();
        while(desayunos.next())
        {
            QString idcomida = desayunos.value(0).toString();
            QString tipo = desayunos.value(1).toString();
            QString nombre = desayunos.value(2).toString();
            QString raciones = desayunos.value(3).toString();

            ui->inventario_Tabla->insertRow(ui->inventario_Tabla->rowCount());

            if(raciones.toInt()<=10)
            {
             ui->inventario_Tabla->setItem(ui->inventario_Tabla->rowCount()-1,0,new QTableWidgetItem("Pocos Recursos"));
             ui->inventario_Tabla->item(ui->inventario_Tabla->rowCount()-1,0)->setBackgroundColor("red");
            ui->inventario_Tabla->item(ui->inventario_Tabla->rowCount()-1,0)->setTextAlignment(Qt::AlignCenter);
            }else
            {
             ui->inventario_Tabla->setItem(ui->inventario_Tabla->rowCount()-1,0,new QTableWidgetItem("Suficientes Recursos"));
            ui->inventario_Tabla->item(ui->inventario_Tabla->rowCount()-1,0)->setBackgroundColor("green");
            ui->inventario_Tabla->item(ui->inventario_Tabla->rowCount()-1,0)->setTextAlignment(Qt::AlignCenter);
            }

            ui->inventario_Tabla->setItem(ui->inventario_Tabla->rowCount()-1,1,new QTableWidgetItem(raciones));
            ui->inventario_Tabla->setItem(ui->inventario_Tabla->rowCount()-1,2,new QTableWidgetItem(nombre));
            ui->inventario_Tabla->setItem(ui->inventario_Tabla->rowCount()-1,3,new QTableWidgetItem(tipo));
            ui->inventario_Tabla->setItem(ui->inventario_Tabla->rowCount()-1,4,new QTableWidgetItem(idcomida));
        }

}

void gerente::on_pushButton_3_clicked()
{
    ui->inventario_Tabla->setRowCount(0);
    QSqlQuery bebidas;
    bebidas.prepare("SELECT idComida,tipo,nombre,raciones from comida where tipo='Bebidas'");
    bebidas.exec();
    while(bebidas.next())
    {
        QString idcomida = bebidas.value(0).toString();
        QString tipo = bebidas.value(1).toString();
        QString nombre = bebidas.value(2).toString();
        QString raciones = bebidas.value(3).toString();

        ui->inventario_Tabla->insertRow(ui->inventario_Tabla->rowCount());

        if(raciones.toInt()<=10)
        {
         ui->inventario_Tabla->setItem(ui->inventario_Tabla->rowCount()-1,0,new QTableWidgetItem("Pocos Recursos"));
         ui->inventario_Tabla->item(ui->inventario_Tabla->rowCount()-1,0)->setBackgroundColor("red");
         ui->inventario_Tabla->item(ui->inventario_Tabla->rowCount()-1,0)->setTextAlignment(Qt::AlignCenter);
        }else
        {
         ui->inventario_Tabla->setItem(ui->inventario_Tabla->rowCount()-1,0,new QTableWidgetItem("Suficientes Recursos"));
        ui->inventario_Tabla->item(ui->inventario_Tabla->rowCount()-1,0)->setBackgroundColor("green");
        ui->inventario_Tabla->item(ui->inventario_Tabla->rowCount()-1,0)->setTextAlignment(Qt::AlignCenter);
        }

        ui->inventario_Tabla->setItem(ui->inventario_Tabla->rowCount()-1,1,new QTableWidgetItem(raciones));
        ui->inventario_Tabla->setItem(ui->inventario_Tabla->rowCount()-1,2,new QTableWidgetItem(nombre));
        ui->inventario_Tabla->setItem(ui->inventario_Tabla->rowCount()-1,3,new QTableWidgetItem(tipo));
        ui->inventario_Tabla->setItem(ui->inventario_Tabla->rowCount()-1,4,new QTableWidgetItem(idcomida));
    }

}

void gerente::on_pushButton_4_clicked()
{
    ui->inventario_Tabla->setRowCount(0);
    QSqlQuery postres;
    postres.prepare("SELECT idComida,tipo,nombre,raciones from comida where tipo='Postres'");
    postres.exec();
    while(postres.next())
    {
        QString idcomida = postres.value(0).toString();
        QString tipo = postres.value(1).toString();
        QString nombre = postres.value(2).toString();
        QString raciones = postres.value(3).toString();

        ui->inventario_Tabla->insertRow(ui->inventario_Tabla->rowCount());

        if(raciones.toInt()<=10)
        {
         ui->inventario_Tabla->setItem(ui->inventario_Tabla->rowCount()-1,0,new QTableWidgetItem("Pocos Recursos"));
         ui->inventario_Tabla->item(ui->inventario_Tabla->rowCount()-1,0)->setBackgroundColor("red");
        ui->inventario_Tabla->item(ui->inventario_Tabla->rowCount()-1,0)->setTextAlignment(Qt::AlignCenter);
        }else{
         ui->inventario_Tabla->setItem(ui->inventario_Tabla->rowCount()-1,0,new QTableWidgetItem("Suficientes Recursos"));
        ui->inventario_Tabla->item(ui->inventario_Tabla->rowCount()-1,0)->setBackgroundColor("green");
        ui->inventario_Tabla->item(ui->inventario_Tabla->rowCount()-1,0)->setTextAlignment(Qt::AlignCenter);
        }

        ui->inventario_Tabla->setItem(ui->inventario_Tabla->rowCount()-1,1,new QTableWidgetItem(raciones));
        ui->inventario_Tabla->setItem(ui->inventario_Tabla->rowCount()-1,2,new QTableWidgetItem(nombre));
        ui->inventario_Tabla->setItem(ui->inventario_Tabla->rowCount()-1,3,new QTableWidgetItem(tipo));
        ui->inventario_Tabla->setItem(ui->inventario_Tabla->rowCount()-1,4,new QTableWidgetItem(idcomida));
    }
}

void gerente::on_pushButton_5_clicked()
{
    QString html;
    html +="<img class='imageCenter' text-align: 'center' src='://img/Iconos/logo.jpeg' alt='Ed' width='200' height='130'/><strong>"
           "<h1 style='text-align: center';>Inventario</h1>"
           "<hr />"
           "<h3 style='text-align: center';>Presentamos el siguiente inventario de todos los prudctos producidos y vendidos por nosotros</h3>"
           "<p><h2>ID&nbsp; &nbsp; &nbsp;Tipo&nbsp; &nbsp; &nbsp;Nombre&nbsp; &nbsp; &nbsp; Raciones</h2></p>"
           "<hr />";

    QSqlQuery postres;
    postres.prepare("SELECT idComida,tipo,nombre,raciones from comida");
    postres.exec();
    while(postres.next())
    {
        QString idcomida = postres.value(0).toString();
        QString tipo = postres.value(1).toString();
        QString nombre = postres.value(2).toString();
        QString raciones = postres.value(3).toString();
    html +="<br>"+idcomida+"&nbsp; &nbsp; &nbsp; "+tipo+"&nbsp; &nbsp; &nbsp; "+nombre+" &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp;"+raciones+"<hr />";
    }


    QTextDocument document;
    document.setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName("/tmp/Inventario.pdf");
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    document.print(&printer);
    QDesktopServices::openUrl(QUrl::fromLocalFile("/tmp/Inventario.pdf"));
}

