package cn.edu.hit.util;

import java.sql.*;

public class DbUtil {

    private static Connection con;
    private static final String URL = "jdbc:postgresql://localhost:5432/task02";
    private static final String USERNAME = "postgres";
    private static final String PASSWORD = "alpine";

    private static Connection createConnection() {
        try {
            Class.forName("org.postgresql.Driver");
            con = DriverManager.getConnection(URL, USERNAME, PASSWORD);
        } catch (ClassNotFoundException | SQLException e) {
            throw new RuntimeException(e);
        }
        return con;
    }

    public static Connection getConnection() {
        try {
            if (con == null || con.isClosed()) {
                con = createConnection();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return con;
    }

    public static void closeConnection(Connection connection) {
        try {
            if (connection != null && !connection.isClosed()) {
                connection.close();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public static void closeAll(Connection connection, PreparedStatement ps) {
        try {
            if (connection != null && !connection.isClosed()) {
                connection.close();
            }
            if (ps != null && !ps.isClosed()) {
                ps.close();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public static void closeAll(Connection connection, PreparedStatement ps, ResultSet rs) {
        try {
            if (connection != null && !connection.isClosed()) {
                connection.close();
            }
            if (ps != null && !ps.isClosed()) {
                ps.close();
            }
            if (rs != null && !rs.isClosed()) {
                rs.close();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

}
