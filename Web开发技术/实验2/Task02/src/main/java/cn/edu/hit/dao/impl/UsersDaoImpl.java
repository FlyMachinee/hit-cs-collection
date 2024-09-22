package cn.edu.hit.dao.impl;

import cn.edu.hit.dao.UsersDao;
import cn.edu.hit.entity.User;
import cn.edu.hit.util.DbUtil;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UsersDaoImpl implements UsersDao {
    @Override
    public Boolean insert(User user) {
        if (isExist(user.getUsername())) {
            return false;
        }
        Connection con = DbUtil.getConnection();
        PreparedStatement ps = null;
        try {
            ps = con.prepareStatement("insert into users values(?, ?)");
            ps.setString(1, user.getUsername());
            ps.setString(2, user.getPassword());

            ps.executeUpdate();
        } catch (SQLException e) {
            return false;
        } finally {
            DbUtil.closeAll(con, ps);
        }

        return true;
    }

    @Override
    public Boolean isMatch(User user) {
        Connection con = DbUtil.getConnection();
        PreparedStatement ps = null;
        ResultSet rs = null;

        Boolean result = false;

        try {
            ps = con.prepareStatement("select * from users where username=? and password=?");
            ps.setString(1, user.getUsername());
            ps.setString(2, user.getPassword());

            rs = ps.executeQuery();
            if (rs.next()) {
                result = true;
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        } finally {
            DbUtil.closeAll(con, ps, rs);
        }
        return result;
    }

    @Override
    public Boolean isExist(String username) {
        Connection con = DbUtil.getConnection();
        PreparedStatement ps = null;
        ResultSet rs = null;

        Boolean result = false;

        try {
            ps = con.prepareStatement("select * from users where username=?");
            ps.setString(1, username);

            rs = ps.executeQuery();
            if (rs.next()) {
                result = true;
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        } finally {
            DbUtil.closeAll(con, ps, rs);
        }
        return result;
    }
}
