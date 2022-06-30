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

