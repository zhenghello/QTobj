


#include "FtreeExcel.h"

FtreeExcel::FtreeExcel(QString jsonName ,bool hideKey, QWidget *parent) :QWidget(parent)
{
    // 外框设置
    if (this->objectName().isEmpty())this->setObjectName("Tree");
    this->resize(300, 600);
    this->setMinimumSize(QSize(250, 200));
    QPalette palette;
    palette.setColor(QPalette::Background,QColor(250,100,250));
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    this->setWindowTitle("Tree");
    this->setWindowFlags(Qt::Window);   // 默认外框
    // 外框布局
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(2);
    verticalLayout->setObjectName("verticalLayout");
    verticalLayout->setContentsMargins(2, 2, 2, 2);
    // 树    显示
    tree = new QTreeWidget(this);
    tree->setObjectName("tree");
    tree->setMinimumSize(QSize(200, 100));
    tree->setMaximumSize(QSize(1000,1000));
    QFont font;
    font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
    font.setPointSize(8);
    tree->setFont(font);
    tree->setStyleSheet("");
    tree->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    tree->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    verticalLayout->addWidget(tree);
    tree->header()->setSectionsMovable(false);              // 左右不能拖动
    // 上下拖动
    tree->setDragEnabled(true);
    tree->setDefaultDropAction(Qt::MoveAction);
    tree->setDragDropMode(QAbstractItemView::DragDrop);
    // 背景属性
    tree->setStyleSheet("QTreeWidget::item{border: 1px solid rgb(200, 200, 200);background-color: rgb(200, 255, 255);height: 25px}QTreeWidget::item:selected{background-color:rgb(255,0,0,100)}");
    // 设置提示
    tree->header()->setToolTip(QString::fromLocal8Bit("想要修改列宽或者修改表头名,到json文件中修改,+是增列,-是减列,行可以拖拽"));

    // 隐藏框的内容
    frame_hide = new QFrame(this);
    frame_hide->setObjectName("frame_hide");
    frame_hide->setMinimumSize(QSize(100, 80));
    frame_hide->setMaximumSize(QSize(1000, 200));
    QPalette palette1;
    palette1.setColor(QPalette::Background,QColor(85,255,255));
    frame_hide->setAutoFillBackground(true);
    frame_hide->setPalette(palette1);
    // 隐藏框的布局
    gridLayout = new QGridLayout(frame_hide);
    gridLayout->setSpacing(1);
    gridLayout->setObjectName("gridLayout");
    gridLayout->setContentsMargins(1, 1, 1, 1);
    // 文本 标签1
    lineEdit = new QLineEdit(frame_hide);
    lineEdit->setObjectName("lineEdit");
    lineEdit->setStyleSheet("background-color: rgb(0, 255, 127);");
    lineEdit->setText(jsonName);
    gridLayout->addWidget(lineEdit, 0, 1, 1, 6);

    // 按键1排
    button[0] = new QPushButton(frame_hide);
    button[0]->setText(QString::fromLocal8Bit("导入"));
    gridLayout->addWidget(button[0], 1, 1, 1, 1);
    button[1] = new QPushButton(frame_hide);
    button[1]->setText(QString::fromLocal8Bit("导出"));
    gridLayout->addWidget(button[1], 1, 2, 1, 1);
    button[2] = new QPushButton(frame_hide);
    button[2]->setText(QString::fromLocal8Bit("打开"));
    gridLayout->addWidget(button[2], 1, 3, 1, 1);
    button[3] = new QPushButton(frame_hide);
    button[3]->setText(QString::fromLocal8Bit("文件名"));
    gridLayout->addWidget(button[3], 1, 4, 1, 1);
    button[4] = new QPushButton(frame_hide);
    button[4]->setText(QString::fromLocal8Bit("--"));
    gridLayout->addWidget(button[4], 1, 5, 1, 1);
    button[5] = new QPushButton(frame_hide);
    button[5]->setText(QString::fromLocal8Bit("--"));
    gridLayout->addWidget(button[5], 1, 6, 1, 1);


    // 按键2排
    button[6] = new QPushButton(frame_hide);
    button[6]->setText(QString::fromLocal8Bit("--"));
    gridLayout->addWidget(button[6], 2, 1, 1, 1);
    button[7] = new QPushButton(frame_hide);
    button[7]->setText(QString::fromLocal8Bit("--"));
    gridLayout->addWidget(button[7], 2, 2, 1, 1);
    button[8] = new QPushButton(frame_hide);
    button[8]->setText(QString::fromLocal8Bit("--"));
    gridLayout->addWidget(button[8], 2, 3, 1, 1);
    button[9] = new QPushButton(frame_hide);
    button[9]->setText(QString::fromLocal8Bit("--"));
    gridLayout->addWidget(button[9], 2, 4, 1, 1);
    button[10] = new QPushButton(frame_hide);
    button[10]->setText(QString::fromLocal8Bit("--"));
    gridLayout->addWidget(button[10], 2, 5, 1, 1);
    button[11] = new QPushButton(frame_hide);
    button[11]->setText(QString::fromLocal8Bit("--"));
    gridLayout->addWidget(button[11], 2, 6, 1, 1);
    verticalLayout->addWidget(frame_hide);// 添加隐藏框
    // 设置按键的范围
//    for(int i=0;i<12;i++)
//    {
//        button[i]->setMinimumWidth(100);
//    }

    // 自定义设置
    hide_key(hideKey);  // 默认设置隐藏

    // 按键关联部分
    connect(button[0],SIGNAL(clicked()),this,SLOT(click_button00()));
    connect(button[1],SIGNAL(clicked()),this,SLOT(click_button01()));
    connect(button[2],SIGNAL(clicked()),this,SLOT(click_button02()));
    connect(button[3],SIGNAL(clicked()),this,SLOT(click_button03()));
    connect(button[4],SIGNAL(clicked()),this,SLOT(click_button04()));
    connect(button[5],SIGNAL(clicked()),this,SLOT(click_button05()));

    connect(button[6],SIGNAL(clicked()),this,SLOT(click_button06()));
    connect(button[7],SIGNAL(clicked()),this,SLOT(click_button07()));
    connect(button[8],SIGNAL(clicked()),this,SLOT(click_button08()));
    connect(button[9],SIGNAL(clicked()),this,SLOT(click_button09()));
    connect(button[10],SIGNAL(clicked()),this,SLOT(click_button10()));
    connect(button[11],SIGNAL(clicked()),this,SLOT(click_button11()));

    connect(tree,SIGNAL(pressed(QModelIndex)),this,SLOT( press_tree(QModelIndex)));// 树形点击关联
    // 自动导入tree文件

    excel2treeWidget(tree,lineEdit->text());
    setTreeItemIsEditable(tree);    // 允许编辑
}
FtreeExcel::~FtreeExcel()
{
    // 退出时自动导出tree文件
    treeWidget2excel(tree,lineEdit->text());
}
// 函数功能:隐藏按键
void FtreeExcel::hide_key(bool hide)
{
    if(hide)frame_hide->hide();
      else  frame_hide->show();
}
// 函数功能:获取文件名
QString FtreeExcel::getJsonName(void)
{
    return lineEdit->text();
}
// 函数功能:查找关键词，并返回对应的item
const QTreeWidgetItem* FtreeExcel::findKeyWord(int column, QString key)
{
    return treeFindKey(tree,column,key);
}


// 按键触发功能
// 导入json文件
void FtreeExcel::click_button00()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(nullptr == fileName)return;  // 没有选择就取消
    fileName.replace ("/","\\");
    //lineEdit->setText (fileName); // 修改文件名
    excel2treeWidget(tree,lineEdit->text());
    setTreeItemIsEditable(tree);    // 允许编辑
}
// 导出json文件
void FtreeExcel::click_button01()
{
    QString fileName = QFileDialog::getSaveFileName(this,"new.json","*.json");
    if(nullptr == fileName)return; // 没有选择就取消
    fileName.replace ("/","\\");
    lineEdit->setText (fileName);
    treeWidget2excel(tree,lineEdit->text());
}
// 打开文件->用于编辑
void FtreeExcel::click_button02()
{
    QString str1 = "explorer " + lineEdit->text();
    QProcess::execute(str1);
    qDebug()<<"click_button02";
}
//
void FtreeExcel::click_button03()
{

}
void FtreeExcel::click_button04()
{

}
void FtreeExcel::click_button05()
{

}
void FtreeExcel::click_button06()
{

}
void FtreeExcel::click_button07()
{

}
void FtreeExcel::click_button08()
{

}
//
void FtreeExcel::click_button09()
{

}
//
void FtreeExcel::click_button10()
{

}
void FtreeExcel::click_button11()
{

}
// 当前选择下 新增子层
void FtreeExcel::treeAddChild()
{
    // 判断是否选中
    if(tree->currentItem() == NULL)
    {
        return;
    }
    // 新增节点
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0,"new"+QString::number(tree->currentItem()->childCount()));
    tree->currentItem()->addChild(item);
    setTreeItemIsEditable(item);            // 设置可编辑
    tree->currentItem()->setExpanded(true); // 展开 当前节点
}
// 当前选择下 减少
void FtreeExcel::treeDecChose()
{
    // 没有选择不操作
    if(tree->currentIndex().row() ==  -1)return;
    // 删除节点
    delTreeItem(tree->currentItem());
}
// 当前选择下 新增
void FtreeExcel::treeAddChose()
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0,"new"+QString::number(tree->topLevelItemCount()));
    // 判断是否选中
    if(tree->currentItem() == NULL)
    {
        tree->insertTopLevelItem(tree->topLevelItemCount(),item);
        item->setText(0,"new"+QString::number(tree->topLevelItemCount()));
    }
    // 判断是否在顶层
    else if(-1==tree->indexOfTopLevelItem(tree->currentItem()))
    {   // 不在顶层
        item->setText(0,"new"+QString::number(tree->currentItem()->parent()->childCount()));
        tree->currentItem()->parent()->insertChild(tree->currentIndex().row()+1,item);
    }
    else
    {   // 在顶层
        tree->insertTopLevelItem(tree->indexOfTopLevelItem(tree->currentItem())+1,item);
        item->setText(0,"new"+QString::number(tree->topLevelItemCount()));
    }
    setTreeItemIsEditable(item);
}
// 按下树的单元格
void FtreeExcel::press_tree(QModelIndex index)
{
    // 0.只有右击触发有用
    if( qApp->mouseButtons() != Qt::RightButton)return ;
    qDebug()<<index;
    // 1.增加行 - 倒数第2列
    if(index.column() == (tree->columnCount()-2))
    {
        treeAddChose();
    }
    // 2.减少行
    if(index.column() == (tree->columnCount()-1))
    {
        treeDecChose();
    }
}
