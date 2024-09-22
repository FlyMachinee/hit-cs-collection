package cn.edu.hit.servlet;

import cn.edu.hit.dao.UsersDao;
import cn.edu.hit.dao.impl.UsersDaoImpl;
import cn.edu.hit.entity.User;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.io.PrintWriter;


@WebServlet(name = "loginServlet", value = "/login-servlet")
public class LoginServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String trueJson = "{ \"isOk\": true }";
        String falseJson = "{ \"isOk\": false }";
        response.setContentType("application/json");
        response.setCharacterEncoding("UTF-8");
        PrintWriter out = response.getWriter();

        String username = request.getParameter("username");
        String password = request.getParameter("password");
        UsersDao dao = new UsersDaoImpl();
        if (dao.isMatch(new User(username, password))) {
            out.println(trueJson);
        }
        else {
            out.println(falseJson);
        }
        out.flush();
        out.close();
    }
}
