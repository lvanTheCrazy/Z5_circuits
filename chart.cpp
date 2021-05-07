#include "chart.h"
#include "ui_chart.h"

Chart::Chart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chart)
{
    ui->setupUi(this);
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    scene = new QGraphicsScene();
    scene_1 = new QGraphicsScene();
    //    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

Chart::~Chart()
{
    delete ui;
}

QVector<double> furie(QVector<double> t, QVector<double> A, QVector<double> psi, QVector<double> W){
    QVector<double> temp;
    int i = 0;
    double sum = 0;
    for (int Tx = 0; Tx<t.size(); Tx++){
        temp.push_back(0);
        sum+=A[0];
        for (i = 1; i<t.size(); i++){
            sum+=A[i]*sin(i*W[i]*t[Tx]+psi[i]);
        }
        temp[Tx]=sum;
        sum=0;
    }
    return temp;
}

void Chart::build(QVector<double> t, QVector<double> xn)
{
    ui->graphicsView->setScene(scene);
    scene->clear();
    ui->graphicsView->scale(1/scaling,1/scaling);
    QBrush bruh;
    QPen pen(Qt::DashLine);
    pen.setColor("orange");
    pen.setWidth(1);
    QPointF point;
    double upper_y_border = 50 + 100 * *std::max_element(xn.begin(), xn.end());
    double upper_x_border = 50 + 100 * *std::max_element(t.begin(), t.end());
    double lower_y_border;
    if(*std::min_element(xn.begin(), xn.end()) < 0){
        lower_y_border = 50  - 100 * *std::min_element(xn.begin(), xn.end());
    }
    else{
        lower_y_border = 50;
    }

    //////////////////////////////////////

    //пример
    //    for(int i = 0; i < 100; i++)
    //        points.append(QPointF((i+2)*5, 250+50*sin((i+2)*50)));

    //рыжае

    for (int i = 0; i < upper_x_border/10; i++){
        scene->addLine(10+i*10, 0, 10+i*10, upper_y_border+lower_y_border, pen);
    }

    for (int i = 0; i < (upper_y_border+lower_y_border)/10; i++){
        scene->addLine(0, 10+i*10, upper_x_border, 10+i*10, pen);
    }


    pen.setWidth(2);


    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);

    //чорнае
    x_axis = QLineF(0, upper_y_border, upper_x_border, upper_y_border);
    y_axis = QLineF(10, 0, 10, upper_y_border+lower_y_border);
    scene->addLine(10, 0, 10, upper_y_border+lower_y_border, pen);
    scene->addLine(0, upper_y_border, upper_x_border, upper_y_border, pen);
    //подписи осей
    QFont font;
    font.setBold(true); font.setFamily("Times");
    QGraphicsTextItem *text;

    text = scene->addText("a(t)",font);
    text->setPos(10, 0);
    text->setDefaultTextColor(Qt::black);

    text = scene->addText("t",font);
    text->setPos(upper_x_border-20, upper_y_border - 20);
    text->setDefaultTextColor(Qt::black);


    /////////////////////////////////////

    for (int i=0; i<t.size()-1; i++){
        //xn
        point.setX(10+100*t[i]);
        point.setY(upper_y_border-100*xn[i]);
        pen.setColor(Qt::gray);
        scene->addLine(point.x(), point.y(), 10+100*t[i+1], upper_y_border-100*xn[i+1], pen);
        pen.setColor(Qt::blue);
        scene->addEllipse(point.x(),point.y(),1,1,pen,bruh);
    }

    if(x_axis.length()>y_axis.length()){
        scaling = 0.9*(589/x_axis.length());
    }
    else{
        scaling = 0.9*(407/y_axis.length());
    }

    ui->graphicsView->scale(scaling,scaling);
}

void Chart::build_spectre(QVector<double> A, QVector<double> psi, QVector<double> W)
{
    scene_1->clear();
    QPen pen(Qt::DashLine);
    pen.setColor("orange");
    pen.setWidth(1);
    QPointF point;
    double upper_y_border = 50 + 100 * *std::max_element(A.begin(), A.end());
    double upper_x_border = 50 + 10 * (*std::max_element(W.begin(), W.end())/2);

    //рыжае
    for (int i = 0; i < upper_x_border/10; i++){
        scene_1->addLine(10+i*10, 0, 10+i*10, upper_y_border, pen);
    }

    for (int i = 0; i < (upper_y_border)/10; i++){
        scene_1->addLine(0, 10+i*10, upper_x_border, 10+i*10, pen);
    }


    pen.setWidth(2);


    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);

    //чорнае
    x_axis_spectre = QLineF(0, upper_y_border, upper_x_border, upper_y_border);
    y_axis_spectre = QLineF(10, 0, 10, upper_y_border);
    scene_1->addLine(10, 0, 10, upper_y_border, pen);
    scene_1->addLine(0, upper_y_border, upper_x_border, upper_y_border, pen);

    //подписи осей
    QFont font;
    font.setBold(true); font.setFamily("Times");
    QGraphicsTextItem *text;

    text = scene_1->addText("A(ν)",font);
    text->setPos(10, 0);
    text->setDefaultTextColor(Qt::black);

    text = scene_1->addText("ν",font);
    text->setPos(upper_x_border-20, upper_y_border - 20);
    text->setDefaultTextColor(Qt::black);


    pen.setColor(Qt::green);
    for (int i=0; i<W.size()/2-1; i++){
        //xn
        point.setX(10+10*W[i]);
        point.setY(upper_y_border-100*A[i]);
        scene_1->addLine(point.x(), point.y(), 10+10*W[i+1], upper_y_border-100*A[i+1], pen);
    }
}

void Chart::on_pushButton_clicked()
{
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scale(1/scaling,1/scaling);

    if(x_axis.length()>y_axis.length()){
        scaling = 0.9*(589/x_axis.length());
    }
    else{
        scaling = 0.9*(407/y_axis.length());
    }

    ui->graphicsView->scale(scaling,scaling);

}

void Chart::on_pushButton_2_clicked()
{
    ui->graphicsView->setScene(scene_1);
    ui->graphicsView->scale(1/scaling,1/scaling);

    if(x_axis_spectre.length()>y_axis_spectre.length()){
        scaling = 0.9*(589/x_axis_spectre.length());
    }
    else{
        scaling = 0.9*(407/y_axis_spectre.length());
    }

    ui->graphicsView->scale(scaling,scaling);
}

void Chart::on_pushButton_3_clicked()
{
    //    QString fileName = "file_name.jpg";
    //    QPixmap pixMap = ui->graphicsView->grab(ui->graphicsView->sceneRect().toRect());
    //    pixMap.save(fileName);

    scene->setSceneRect(scene->itemsBoundingRect());
    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    scene->render(&painter);
    image.save("исходный_график.jpg");

    scene_1->setSceneRect(scene_1->itemsBoundingRect());
    QImage image_1(scene_1->sceneRect().size().toSize(), QImage::Format_ARGB32);
    image_1.fill(Qt::white);

    QPainter painter_1(&image_1);
    scene_1->render(&painter_1);
    image_1.save("спектр.jpg");

}

void Chart::on_pushButton_4_clicked()
{
    ui->graphicsView->scale(0.9,0.9);
}

void Chart::on_pushButton_5_clicked()
{

    ui->graphicsView->scale(1.12,1.12);
}

void Chart::on_pushButton_6_clicked()
{
    ui->graphicsView->resetTransform();
    scaling = 1;
}
