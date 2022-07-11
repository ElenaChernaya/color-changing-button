#include <QApplication>
#include <QtWidgets>
#include <QPushButton>
#include <QSlider>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>

#include <iostream>

class Image : public QPushButton
{
Q_OBJECT
private:
    QPixmap mCurrentImage;
    QPixmap mRedImage;
    QPixmap mGreenImage;
    QPixmap mYellowImage;
public:
    Image() = default;
    Image(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    QSize sizeHint() const override;
public slots:
    void setRed();
    void setGreen();
    void setYellow();
    void changeColor(int newValue);
};

Image::Image(QWidget *parent)
{
    setParent(parent);
    mRedImage = QPixmap("C:\\Users\\Elena\\Desktop\\red.jpg");
    mGreenImage = QPixmap("C:\\Users\\Elena\\Desktop\\green.jpg");
    mYellowImage = QPixmap("C:\\Users\\Elena\\Desktop\\yellow.jpg");

    mCurrentImage = mRedImage;

}

void Image::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurrentImage);
}

QSize Image::sizeHint() const
{
    return QSize(300, 300);
}

void Image::setRed()
{
    mCurrentImage = mRedImage;
    update();
}

void Image::setGreen()
{
    mCurrentImage = mGreenImage;
    update();
}

void Image::setYellow()
{
    mCurrentImage = mYellowImage;
    update();
}


void Image::changeColor(int newValue)
{
    if(newValue <= 25)
    {
        setRed();
    }
    else if (newValue > 25 && newValue <= 50)
    {
        setGreen();
    }
    else if (newValue > 50 && newValue <= 75)
    {
        setYellow();
    }

}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QWidget *window = new QWidget();
    Image circle(nullptr);

    auto *slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(100);

    auto *layout = new QGridLayout(window);
    layout->addWidget(&circle);
    layout->addWidget(slider);

    window->setFixedSize(300,300);
    window->move(500, 200);

    QObject::connect(slider, &QSlider::valueChanged, &circle, &Image::changeColor);

    window->show();

    return app.exec();
}


#include <main.moc>
