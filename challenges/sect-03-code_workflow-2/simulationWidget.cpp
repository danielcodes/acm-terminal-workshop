#include <QtGui>
#include <QtOpenGL>

#include "simulationWidget.h"


SimulationWidget::SimulationWidget(Properties *prop, QWidget *parent)
    :   QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
        zoom(prop->zoom),
        xRot(prop->xRot),
        yRot(prop->yRot),
        zRot(prop->zRot),
        length(prop->length),
        width(prop->width),
        height(prop->height),
        spacing(prop->spacing),
        color(prop->color),
        draw(prop->draw),
        guide(prop->guide),
        source(prop->source),
        function(prop->function),
        sphRadius(0),
        sphOriginX(0),
        sphOriginY(0),
        sphOriginZ(0),
        hist(0),
        histReady(false)
{}//end constructor


void
SimulationWidget::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}//end initializeGL


void
SimulationWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);

    //makes points larger
    glPointSize(2);

    //set x/y/z rotation
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);
    
    //set zoom
    float fraction = this->zoom / 100.0;
    glScalef(fraction, fraction, fraction);

    //paint axis if necessary
    if (this->guide == "axis" || this->guide == "both")
        this->paintAxis();

    //prepare sphere if necessary
    if ((this->source == "function") && (this->function == "sphere"))
        this->prepareSphere();

    //move to lattice center
    glTranslatef(
        -0.5*(float)(this->length - 1)*this->spacing,
        -0.5*(float)(this->width - 1)*this->spacing,
        -0.5*(float)(this->height - 1)*this->spacing);

    //paint outline if necessary
    if (this->guide == "box" || this->guide == "both")
        this->paintOutline();

    //set color
    float opacity = 0.75;
    if (this->color == "red")
        glColor4f(1.0, 0.0, 0.0, opacity);
    else if (this->color == "green")
        glColor4f(0.0, 1.0, 0.0, opacity);
    else if (this->color == "blue")
        glColor4f(0.0, 0.0, 1.0, opacity);
    else
        glColor4f(1.0, 1.0, 1.0, opacity);

    //loop over lattice dimensions
    int i, j, k;
    for (i = 0; i < this->height; i++)
    {
        for (j = 0; j < this->width; j++)
        {
            for (k = 0; k < this->length; k++)
            {
                this->paintLed(k, j, i);

                //advance in the x direction
                glTranslatef(this->spacing, 0.0, 0.0);
            }

            //retreat in the x direction and advance in the
            //y direction
            glTranslatef(-1 * this->length * this->spacing,
                this->spacing, 0.0);
        }

        //retreat in the y direction and advance in the z direction
        glTranslatef(0.0, -1 * this->width * this->spacing,
            this->spacing);
    }
}//end paintGL


void
SimulationWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-2.0, 2.0, -2.0, 2.0, 1.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
}//end resizeGL


void
SimulationWidget::mousePressEvent(QMouseEvent *event)
{
    this->lastPos = event->pos();
}//end mousePressEvent


void
SimulationWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - this->lastPos.x();
    int dy = event->y() - this->lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        setXRot(this->xRot + dy);
        setYRot(this->yRot + dx);
    }
    else if (event->buttons() & Qt::RightButton)
        setZRot(this->zRot + dx);

    this->lastPos = event->pos();
}//end mouseMoveEvent


void
SimulationWidget::normalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360; 
    while (angle > 360)
        angle -= 360; 
}//end normalizeAngle


void
SimulationWidget::paintAxis()
{
    int factor = 2;

    //set color to yellow
    glColor4f(1.0, 1.0, 0.0, 1.0);

    glBegin(GL_LINES);

    glVertex3f(-factor * this->length, 0, 0); 
    glVertex3f(factor * this->length, 0, 0); 

    glVertex3f(0, -factor * this->width, 0); 
    glVertex3f(0, factor * this->width, 0); 

    glVertex3f(0, 0, -factor * this->height); 
    glVertex3f(0, 0, factor * this->height);

    glEnd();
}//end paintAxis


void
SimulationWidget::paintOutline()
{
    float start = -0.5;
    float dimX = (float)(this->length - 1)*this->spacing + 0.5;
    float dimY = (float)(this->width - 1)*this->spacing + 0.5;
    float dimZ = (float)(this->height - 1)*this->spacing + 0.5;

    //set color to yellow
    glColor4f(1.0, 1.0, 0.0, 1.0);

    glBegin(GL_LINES);

    //bottom face
    glVertex3f(start, start, start);
    glVertex3f(dimX, start, start);
    glVertex3f(dimX, start, start);
    glVertex3f(dimX, start, dimZ);
    glVertex3f(dimX, start, dimZ);
    glVertex3f(start, start, dimZ);
    glVertex3f(start, start, dimZ);
    glVertex3f(start, start, start);

    //top face
    glVertex3f(start, dimY, start);
    glVertex3f(dimX, dimY, start);
    glVertex3f(dimX, dimY, start);
    glVertex3f(dimX, dimY, dimZ);
    glVertex3f(dimX, dimY, dimZ);
    glVertex3f(start, dimY, dimZ);
    glVertex3f(start, dimY, dimZ);
    glVertex3f(start, dimY, start);

    //vertical connections between top and bottom
    glVertex3f(start, start, start);
    glVertex3f(start, dimY, start);
    glVertex3f(dimX, start, start);
    glVertex3f(dimX, dimY, start);
    glVertex3f(dimX, start, dimZ);
    glVertex3f(dimX, dimY, dimZ);
    glVertex3f(start, start, dimZ);
    glVertex3f(start, dimY, dimZ);

    glEnd();
}//end paintOutline


void
SimulationWidget::paintLed(int x, int y, int z)
{
    bool doPainting = true;

    //math for sine function
    if ((this->source == "function") && (this->function == "sine"))
    {
        float pi = 3.14;
        int sine = round(
            4 * sin(pi/4 * x) +
            4 * sin(pi/4 * z) + 
            (this->width - 2) * 0.5);

        doPainting = y == sine;
    }
    //math for sphere function
    else if ((this->source == "function") && 
        (this->function == "sphere"))
    {
        int sphere = round(
            pow(x - this->sphOriginX, 2.0) + 
            pow(y - this->sphOriginY, 2.0) + 
            pow(z - this->sphOriginZ, 2.0)); 

        doPainting = abs(pow(this->sphRadius - 1, 2) - sphere) < 3;
    }

    //check point cloud file histogram
    else if ((this->source == "file") && this->histReady)
    {
        int index = x +
            this->length * y +
            this->length * this->width * z;
        doPainting = this->hist[index] > 0;
    }
    //paint cube or points if necessary
    if (doPainting)
    {
        if (this->draw == "cubes")  this->paintCube();
        else
        {
            glBegin(GL_POINTS);
            glVertex3f(0, 0, 0); 
            glEnd();
        } 
    }
}//end paintLed


void
SimulationWidget::paintCube()
{
	float dimension = 0.5;

    glBegin(GL_QUADS);

    //bottom
    glVertex3f(  dimension, -dimension, -dimension);
    glVertex3f(  dimension, -dimension,  dimension);
    glVertex3f( -dimension, -dimension,  dimension);
    glVertex3f( -dimension, -dimension, -dimension);

    //top
    glVertex3f(  dimension,  dimension,  dimension);
    glVertex3f(  dimension,  dimension, -dimension);
    glVertex3f( -dimension,  dimension, -dimension);
    glVertex3f( -dimension,  dimension,  dimension);

    //left
    glVertex3f( -dimension, -dimension,  dimension);
    glVertex3f( -dimension,  dimension,  dimension);
    glVertex3f( -dimension,  dimension, -dimension);
    glVertex3f( -dimension, -dimension, -dimension);

    //right
    glVertex3f(  dimension, -dimension, -dimension);
    glVertex3f(  dimension,  dimension, -dimension);
    glVertex3f(  dimension,  dimension,  dimension);
    glVertex3f(  dimension, -dimension,  dimension);

    //front
    glVertex3f( -dimension, -dimension, -dimension);
    glVertex3f( -dimension,  dimension, -dimension);
    glVertex3f(  dimension,  dimension, -dimension);
    glVertex3f(  dimension, -dimension, -dimension);

    //back
    glVertex3f(  dimension, -dimension, dimension);
    glVertex3f(  dimension,  dimension, dimension);
    glVertex3f( -dimension,  dimension, dimension);
    glVertex3f( -dimension, -dimension, dimension);

    glEnd();
}//end paintCube 


void
SimulationWidget::setZoom(int z)
{
    this->zoom = z;
    updateGL();
}//end setZoom


void
SimulationWidget::setXRot(int a)
{
    normalizeAngle(a);
    if (a != xRot) {
        xRot = a;
        emit xRotChanged(a);
        updateGL();
    }
}//end setXRot


void
SimulationWidget::setYRot(int a)
{
    normalizeAngle(a);
    if (a != yRot) {
        yRot = a;
        emit yRotChanged(a);
        updateGL();
    }
}//end setYRot


void
SimulationWidget::setZRot(int a)
{
    normalizeAngle(a);
    if (a != zRot) {
        zRot = a;
        emit zRotChanged(a);
        updateGL();
    }
}//end setZRot


void
SimulationWidget::setLength(int l)
{
    this->length = l;
    updateGL();
}//end set


void
SimulationWidget::setWidth(int w)
{
    this->width = w;
    updateGL();
}//end set


void
SimulationWidget::setHeight(int h)
{
    this->height = h;
    updateGL();
}//end set


void
SimulationWidget::setSpacing(double s)
{
    this->spacing = s;
    updateGL();
}//end setSpacing


void
SimulationWidget::setColor(const QString &c)
{
    this->color = c.toLower();
    this->updateGL();
}//end setColor


void
SimulationWidget::setDraw(const QString &d)
{
    this->draw = d.toLower();
    this->updateGL();
}//end setDraw


void
SimulationWidget::setGuide(const QString &g)
{
    this->guide = g.toLower();
    this->updateGL();
}//end setGuide


void
SimulationWidget::setSource(QAbstractButton *b)
{
    QString text = b->text(), newSrc;

    if (text.contains("no input", Qt::CaseInsensitive))
        newSrc = "no input";
    else if (text.contains("function", Qt::CaseInsensitive))
        newSrc = "function";
    else
        newSrc = "file";

    if (newSrc != this->source)
    {
        this->source = newSrc;
        this->updateGL();
    }
}//end setSource


void
SimulationWidget::prepareSphere()
{
    //set sphere radius to smallest lattice dimension divided by 2
    int dim;
    if (this->length <= this->width)
        dim = this->length;
    else
        dim = this->width;
    if (this->height <= dim)
        dim = this->height;
    this->sphRadius = dim >> 1;

    //set sphere origin coordinates
    this->sphOriginX = this->sphRadius +
        ((this->length % 2) ? 0 : -0.5);
    this->sphOriginY = this->sphRadius +
        ((this->width  % 2) ? 0 : -0.5);
    this->sphOriginZ = this->sphRadius +
        ((this->height % 2) ? 0 : -0.5);
}//end prepareSphere


void
SimulationWidget::setFunction(const QString &f)
{
    this->function = f.toLower();
    this->updateGL();
}//end setFunction


void
SimulationWidget::scanPtCloud(QFile *file)
{
    //confirms that file is readable
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {   
        qDebug() << "Cannot open point cloud file.";
        return;
    }   

    //prepares for 1st pass of file reading
    QTextStream stream(file);
    int numOfPts = stream.readLine().toInt();
    QString line;
    QStringList list;
    double  x, y, z,
            minX, minY, minZ,
            maxX, maxY, maxZ;

    //initializes min/max variables
    line = stream.readLine();
    list = line.split(" ");
    minX = maxX = list.at(0).toDouble();
    minY = maxY = list.at(1).toDouble();
    minZ = maxZ = list.at(2).toDouble();

    //determines min/max
    int i;
    for (i = 0; i < numOfPts - 1; i++)
    {
        line = stream.readLine();
        list = line.split(" ");
        x = list.at(0).toDouble();
        y = list.at(1).toDouble();
        z = list.at(2).toDouble();

        //updates min if necessary
        if (x < minX)
            minX = x;
        if (y < minY)
            minY = y;
        if (z < minZ)
            minZ = z;

        //updates max if necessary
        if (x > maxX)
            maxX = x;
        if (y > maxY)
            maxY = y;
        if (z > maxZ)
            maxZ = z;
    }

    //picks interval size for histogram
    double intervalX, intervalY, intervalZ;
    intervalX = (maxX - minX) / (this->length - 1);
    intervalY = (maxY - minY) / (this->width - 1);
    intervalZ = (maxZ - minZ) / (this->height - 1);

    //prepares histogram array
    if (this->histReady)
        delete[] this->hist;
    int histSize = sizeof(int) * this->length * this->width * 
        this->height;
    int *hist = (int *)malloc(histSize);
    memset(hist, 0, histSize);

    //prepares for 2nd pass of file reading
    stream.seek(0);
    stream.readLine();//throws away first line

    //adds points to histogram
    int offsetX, offsetY, offsetZ, index;
    for (i = 0; i < numOfPts; i++)
    {
        line = stream.readLine();
        list = line.split(" ");

        //determines which histogram interval the point belongs to
        offsetX = ((list.at(0).toDouble() - minX) / intervalX);
        offsetY = ((list.at(1).toDouble() - minY) / intervalY);
        offsetZ = ((list.at(2).toDouble() - minZ) / intervalZ);

        //increments histogram at the appropriate index
        index = offsetX + 
            this->length * offsetY +
            this->length * this->width * offsetZ;
        hist[index]++;
    }

    //stores histogram as a member variable
    this->hist = hist;

    //marks histogram as ready to be draw
    this->histReady = true;
}//end scanPtCloud
