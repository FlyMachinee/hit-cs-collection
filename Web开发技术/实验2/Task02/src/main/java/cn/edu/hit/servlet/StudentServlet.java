package cn.edu.hit.servlet;

import cn.edu.hit.dao.StudentDao;
import cn.edu.hit.dao.impl.StudentDaoImpl;
import cn.edu.hit.entity.Student;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;

import java.io.PrintWriter;
import java.sql.Date;

@WebServlet(name = "studentServlet", value = "/student-servlet")
public class StudentServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String type = request.getParameter("type");

        if (type.equals("selectBySname")) {

            String qname = request.getParameter("qname");
            request.getSession().setAttribute("qname", qname);

        } else if (type.equals("insert")) {

            String sid = request.getParameter("sid");
            StudentDao dao = new StudentDaoImpl();

            response.setContentType("application/json");
            response.setCharacterEncoding("UTF-8");
            PrintWriter out = response.getWriter();

            if (null != dao.selectBySid(sid)) {
                out.println("{\n\t\"insertStatus\": false\n}");
                return;
            }

            String sname = request.getParameter("sname");
            String sgender_text = request.getParameter("sgender");

            Boolean sgender = null;
            if (sgender_text.equals("true"))
                sgender = true;
            else if (sgender_text.equals("false")) {
                sgender = false;
            }

            String sgrade_text = request.getParameter("sgrade");
            Integer sgrade = null;
            if (!sgrade_text.isEmpty())
                sgrade = Integer.valueOf(sgrade_text);

            String sbirthdate_text = request.getParameter("sbirthdate");
            Date sbirthdate = null;
            if (!sbirthdate_text.isEmpty())
                sbirthdate = Date.valueOf(sbirthdate_text);

            String sage_text = request.getParameter("sage");
            Integer sage = null;
            if (!sage_text.isEmpty())
                sage = Integer.valueOf(sage_text);

            Student student = new Student(sid, sname, sgender, sgrade, sbirthdate, sage);
            dao.insert(student);
            out.println("{\n\t\"insertStatus\": true\n}");

            out.flush();
            out.close();

        } else if (type.equals("update")) {
            String sid = request.getParameter("sid");
            StudentDao dao = new StudentDaoImpl();
            Student student = dao.selectBySid(sid);

            String sname = request.getParameter("sname");
            if (sname != null)
                student.setSname(sname);

            String sgender = request.getParameter("sgender");
            if (sgender != null)
                student.setSgender(sgender.equals("undefined") ? null : Boolean.valueOf(sgender));

            String sgrade = request.getParameter("sgrade");
            if (sgrade != null)
                student.setSgrade(sgrade.isEmpty() ? null : Integer.valueOf(sgrade));

            String sbirthdate = request.getParameter("sbirthdate");
            if (sbirthdate != null)
                student.setSbirthdate(sbirthdate.isEmpty() ? null : Date.valueOf(sbirthdate));

            String sage = request.getParameter("sage");
            if (sage != null)
                student.setSage(sage.isEmpty() ? null : Integer.valueOf(sage));

            dao.update(student);

        } else if (type.equals("delete")) {
            String sid = request.getParameter("sid");

            StudentDao dao = new StudentDaoImpl();
            dao.delete(sid);
        }
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        doPost(request, response);
    }
}