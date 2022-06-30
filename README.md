# UKP Helper
GW CPP QT Project

## Goal
帮助北大同学在近期疫情形势严峻的情况下更好地了解校园动态，保障其课业及其他校园生活的便利。程序名称UKP Helper，可以实现PKU Helper的一些简单功能，在其树洞、成绩查询等功能之外，我们的程序还加入了获取BBS，门户网的校园指数等接口，同时实现了将从树洞或BBS上获取到的内容直接通过邮件发送的功能，大大便利了同学们的校园生活。

## Function
### （一）网页功能

**1. 树洞内容查询**

(1) 搜索内容：输入查询关键词和需要搜索的树洞数量，将显示符合条件的所有树洞的洞号和正文。

(2) 关注列表：点击可获取自己关注的所有树洞的洞号和正文。

(3) 获取回复：输入洞号，可以获取这个洞的正文、回复数、关注数和所有回复信息。

(4) 查询成绩：点击可查询自己的GPA和所有课程的成绩，依分数降序和时间倒序分学期输出。

**2. BBS全站热点获取**

点击主界面上的按钮即可获取BBS全站实时的100条热点内容，帮助同学们了解校园动态。

**3. 校园指数查询**

(1) 就餐情况：选择食堂的数量n，程序将自动推荐拥挤程度最低的n个食堂并显示。这里的拥挤程度定义为一个食堂的就餐人数与总容量之比，方便同学们进行就餐食堂的选择。

(2) 场馆推荐：选择一项运动，程序将查询校内所有相应运动场馆的占据情况，即当前占据人数和场馆的总容量并显示。

(3) 空闲教室：选择一栋教学楼，程序将查询该教学楼的空闲教室数和总教室数量并显示，方便同学们进行自习地点的选择。

**4. 门户网入口**

点击主界面上的按钮可自动跳转至北京大学门户网站(https://portal.pku.edu.cn)。

**5. 教学网入口**

点击主界面上的按钮可自动跳转至北京大学教学网(https://course.pku.edu.cn)。

### （二）邮件功能

**1. 树洞部分**

向使用pku邮箱的好友发送树洞上搜集到的信息，包括搜索关键词得到的内容，自己的关注列表，自己的课程成绩。搜集到的内容将自动填充进邮件的正文，只需输入邮箱便可快捷地一键发送了。

**2. BBS部分**

向使用pku邮箱的好友发送BBS全站的100条热点内容，同样输入邮箱便可一键发送。

## 模块和类设计

### （一）mywidget.h

**描述：**

定义了应用程序的主界面窗口

**继承：**

继承自抽象类QWidget

**成员函数列表：**

* on_pushButton_treehole_clicked：打开树洞功能的窗口

* on_pushButton_bbs_clicked：打开BBS功能的窗口
* on_pushButton_campus_clicked：打开校园指数查询功能的窗口
* on_pushButton_portal_clicked：跳转至北京大学门户网
* on_pushButton_course_clicked：跳转至北京大学教学网

**构造函数：**

```C++
MyWidget(QWidget *parent = 0);
```



### （二）treehold.h

**描述：**

定义了实现树洞功能的窗口

**继承：**

继承自抽象类QWidget

**成员函数列表：**

* on_pushButton_token_clicked()：保存用户输入的树洞User Token

* on_pushButton_search_clicked()：根据关键词向网页提交get请求，搜索树洞相关内容
* processSearch(QNetworkReply* reply)：处理搜索树洞返回的json内容，并显示在窗口上
* on_pushButton_attention_clicked()：向网页提交get请求，获得所有树洞关注列表
* processAttention(QNetworkReply* reply)：处理获取树洞关注返回的json内容，并显示在窗口上
* on_pushButton_gpa_clicked()：向网页提交get请求，获得所有课程成绩和综合GPA
* processGPA(QNetworkReply* reply)：处理获取课程成绩返回的json内容，并显示在窗口上
* on_pushButton_comment_clicked()：创建一个comment对象，并打开查询树洞回复的窗口
* treehole_mail()：创建一个MainWindow对象，并打开发送邮件的窗口

**构造函数：**

```c++
treehole(QWidget *parent = nullptr);
```



### （三）comment.h

**描述：**

定义了根据洞号获取树洞所有回复的窗口

**继承：**

继承自抽象类QWidget

**成员函数列表：**

* on_pushButton_comment_clicked()：向网页提交get请求，获得该树洞的基本信息

* processHole(QNetworkReply* reply)：处理上一步返回内容，并提交获取评论的get请求
* processComment(QNetworkReply* reply)：处理返回的json数据，显示树洞的所有回复

**构造函数：**

```c++
comment(QWidget *parent = nullptr);
```



### （四）bbs.h

**描述：**

定义了实现BBS功能的窗口

**继承：**

继承自抽象类QWidget

**成员函数列表：**

* on_pushButton_bbs_clicked()：向BBS网站提交get请求，获取全站热点版面的内容

* processBBS(QNetworkReply *reply)：用正则表达式解析返回的html数据，并显示在窗口上
* bbs_mail()：创建一个MainWindow对象，并打开发送邮件的窗口

**构造函数：**

```C++
bbs(QWidget *parent = nullptr);
```



### （五）campus.h

**描述：**

定义了根据条件查询校园指数的窗口

**继承：**

继承自抽象类QWidget

**成员函数列表：**

* on_pushButton_canteen_clicked()：向北大门户网站提交get请求，获取就餐指数

* processCanteen(QNetworkReply *reply)：处理返回的json，以一定方式排序显示
* on_pushButton_gym_clicked()：向北大门户网站提交get请求，获取健身指数
* processGym(QNetworkReply *reply)：处理返回的json，根据条件显示数据
* on_pushButton_classroom_clicked()：向北大门户网站提交get请求，获取空闲教室
* processClassroom(QNetworkReply *reply)：处理返回的json，根据条件显示数据

**构造函数：**

```c++
campus(QWidget *parent = nullptr);
```



### （六）mainwindow.h

**描述：**

定义了发送邮件的窗口

**继承：**

继承自抽象类QMainWindow

**成员函数列表：**

* sendMail：发送邮件

* MailSent：检查邮件状态并提示

**构造函数：**传入邮件主题、邮件正文。

```c++
MainWindow(QWidget *parent = 0,QString subject="Subject",QString mailbody="MailBody");
```



### （七）smtp.h

**描述：**

定义了具有发送邮件功能的smtp代理

**继承：**

继承自抽象类QObject

**成员函数列表：**

* sendMail，发送邮件

**构造函数：**传入用户名、密码、主服务器等

```c++
Smtp(const QString &user, const QString &pass, const QString &host, int port = 465, int timeout = 30000);
```

