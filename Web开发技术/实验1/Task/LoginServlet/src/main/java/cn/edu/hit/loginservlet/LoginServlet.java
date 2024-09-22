package cn.edu.hit.loginservlet;

import java.io.*;
import jakarta.servlet.http.*;
import jakarta.servlet.annotation.*;


@WebServlet(name = "loginServlet", value = "/login-servlet")
public class LoginServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String trueJson = "{\n" +
                "\t\"isOk\": true\n" +
                "}";
        String falseJson = "{\n" +
                "\t\"isOk\": false\n" +
                "}";
        response.setContentType("application/json");
        response.setCharacterEncoding("UTF-8");
        PrintWriter out = response.getWriter();
        if (request.getParameter("username").equals("admin") && request.getParameter("password").equals("123")) {
            out.println(trueJson);
        }
        else {
            out.println(falseJson);
        }
        out.flush();
        out.close();
    }
}
