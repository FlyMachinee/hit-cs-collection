<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="cn.edu.hit.dao.StudentDao, cn.edu.hit.dao.impl.StudentDaoImpl" %>
<%@ page import="cn.edu.hit.entity.Student, java.util.List" %>
<%@ page import="java.sql.Date" %>

<!DOCTYPE html>

<html>

<head>
  <title>哈尔滨工业大学判官系统</title>

  <script>
    if (sessionStorage.getItem("username") === null)
      window.location.replace("login.html")
  </script>

  <script src="js/jquery-3.7.1.min.js"></script>
  <script src="js/bootstrap/bootstrap.min.js"></script>

  <link rel="stylesheet" href="css/bootstrap/bootstrap.min.css">
  <link rel="stylesheet" href="css/task02.css">

  <script src="js/task02.js"></script>

</head>

<body>

<nav class="navbar navbar-default" role="navigation">
  <div class="container-fluid">
    <div class="navbar-header" style="color: whitesmoke; margin-left: 20px;">
      哈尔滨工业大学判官系统
    </div>
    <div class="nav navbar-nav navbar-right" style="color: whitesmoke; font-size: 13px; padding-right: 10px">
      <span id="username-span">您好！用户</span><a onclick="onExit()" href="login.html">退出登陆</a>
    </div>
  </div>
</nav>

<%
  if (session.getAttribute("qname") == null)
    session.setAttribute("qname", "");
%>

<div class="container">
  <div class="row">
    <div class="col">
      按姓名模糊查询（留空为查询全部）
      <input type="text" id="query-name" placeholder="姓名"
             value="<%= (String)session.getAttribute("qname") %>"
             onchange="query_name_onChange()"
      >
    </div>
  </div>
</div>

<table class="table table-bordered table-striped table-hover">
  <thead>
    <tr>
      <th>#</th>
      <th>学号</th>
      <th>姓名</th>
      <th>性别</th>
      <th>成绩</th>
      <th>出生日期</th>
      <th>年龄</th>
      <th>审判</th>
      <th>修改</th>
      <th>移除</th>
    </tr>
  </thead>

  <tbody>
<%
  String qname = (String)session.getAttribute("qname");
  qname = qname == null ? "" : qname;

  StudentDao dao = new StudentDaoImpl();
  List<Student> studentList = dao.selectBySname(qname);
  String sid, sname;
  Boolean sgender;
  Integer sgrade, sage, rowNum = 0;
  Date sbirthdate;
  for (Student student: studentList) {
    sid = student.getSid();
    sname = student.getSname();
    sgender = student.getSgender();
    sgrade = student.getSgrade();
    sbirthdate = student.getSbirthdate();
    sage = student.getSage();
    ++rowNum;
    %>
    <tr id=<%= "data-" + rowNum %> row=<%= "" + rowNum %>>
      <td><b><%= rowNum %></b></td>
      <td><%= sid %></td>
      <td><%= sname %></td>
      <td style="color: <%= (sgender == null) ? "grey" : "black" %>"><%= (sgender == null) ? "未知" : (sgender ? "男" : "女") %></td>
      <td style="color: <%= (sgrade == null) ? "grey" : (sgrade < 60 ? "red" : "green") %>"><%= sgrade %></td>
      <td style="color: <%= (sbirthdate == null) ? "grey" : "black" %>"><%= sbirthdate %></td>
      <td style="color: <%= (sage == null) ? "grey" : "black" %>"><%= sage %></td>
      <td><button name="judge-button"
           style="visibility: <%= sgrade == null ? "hidden" : "visible" %>"
           onclick="student_live_or_die(<%= rowNum %>)"
        ><%= (sgrade == null || sgrade < 60) ? "大发慈悲，捞！" : "考这么高？挂！"%></button></td>
      <td><button onclick="student_update_start(<%= rowNum %>)">修改</button></td>
      <td><button onclick="student_delete(<%= rowNum %>)">踢出班级</button></td>
    </tr>
<%
  }
%>
    <tr id="add-new-row" onclick="add_new_row_onClick()">
      <td style="background-color: #4D8DDD; color: white"><b>+添加</b></td>
    </tr>

  </tbody>
</table>
</body>

</html>