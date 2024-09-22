package cn.edu.hit.dao.impl;

import cn.edu.hit.dao.StudentDao;
import cn.edu.hit.entity.Student;
import cn.edu.hit.util.DbUtil;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class StudentDaoImpl implements StudentDao {
    @Override
    public void modify(String sql) {
        Connection con = DbUtil.getConnection();
        PreparedStatement ps = null;

        try {
            ps = con.prepareStatement(sql);

            ps.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void insert(Student student) {
        String sid = student.getSid();
        String sname = student.getSname();
        Boolean sgender = student.getSgender();
        Integer sgrade = student.getSgrade();
        Date sbirthdate = student.getSbirthdate();
        Integer sage = student.getSage();

        String sql = "insert into student values(?, ?, ?, ?, ?, ?)";
        Connection con = DbUtil.getConnection();
        PreparedStatement ps = null;
        try {
            ps = con.prepareStatement(sql);
            ps.setString(1, sid);
            ps.setString(2, sname);

            if (sgender != null)
                ps.setBoolean(3, sgender);
            else
                ps.setNull(3, Types.BOOLEAN);

            if (sgrade != null)
                ps.setInt(4, sgrade);
            else
                ps.setNull(4, Types.INTEGER);

            if (sbirthdate != null)
                ps.setDate(5, sbirthdate);
            else
                ps.setNull(5, Types.DATE);

            if (sage != null)
                ps.setInt(6, sage);
            else
                ps.setNull(6, Types.INTEGER);

            ps.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        } finally {
            DbUtil.closeAll(con, ps);
        }
    }

    @Override
    public void update(Student student) {
        String sid = student.getSid();
        String sname = student.getSname();
        Boolean sgender = student.getSgender();
        Integer sgrade = student.getSgrade();
        Date sbirthdate = student.getSbirthdate();
        Integer sage = student.getSage();

        String sql = "update student set sname = ?, sgender = ?, sgrade = ?, sbirthdate = ?, sage = ? where sid = ?";
        Connection con = DbUtil.getConnection();
        PreparedStatement ps = null;

        try {
            ps = con.prepareStatement(sql);
            ps.setString(1, sname);

            if (sgender != null)
                ps.setBoolean(2, sgender);
            else
                ps.setNull(2, Types.BOOLEAN);

            if (sgrade != null)
                ps.setInt(3, sgrade);
            else
                ps.setNull(3, Types.INTEGER);

            if (sbirthdate != null)
                ps.setDate(4, sbirthdate);
            else
                ps.setNull(4, Types.DATE);

            if (sage != null)
                ps.setInt(5, sage);
            else
                ps.setNull(5, Types.INTEGER);

            ps.setString(6, sid);

            ps.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        } finally {
            DbUtil.closeAll(con, ps);
        }
    }

    @Override
    public void delete(String sid) {
        String sql = "delete from student where sid = ?";
        Connection con = DbUtil.getConnection();
        PreparedStatement ps = null;

        try {
            ps = con.prepareStatement(sql);
            ps.setString(1, sid);

            ps.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        } finally {
            DbUtil.closeAll(con, ps);
        }
    }

    @Override
    public List<Student> selectAll() {
        return selectAll("select * from student order by length(sid) asc, sid asc");
    }

    @Override
    public List<Student> selectAll(String sql) {
        Connection con = DbUtil.getConnection();
        PreparedStatement ps;
        ResultSet rs;

        List<Student> res = new ArrayList<>();
        try {
            ps = con.prepareStatement(sql);
            rs = ps.executeQuery();

            while (rs.next()) {
                Student stu = new Student();

                stu.setSid(rs.getString("sid"));
                stu.setSname(rs.getString("sname"));

                Boolean sgender_res = rs.getBoolean("sgender");
                if (rs.wasNull())
                    stu.setSgender(null);
                else
                    stu.setSgender(sgender_res);

                Integer sgrade_res = rs.getInt("sgrade");
                if (rs.wasNull())
                    stu.setSgrade(null);
                else
                    stu.setSgrade(sgrade_res);

                Date sbirthdate_res = rs.getDate("sbirthdate");
                if (rs.wasNull())
                    stu.setSbirthdate(null);
                else
                    stu.setSbirthdate(sbirthdate_res);

                Integer sage_res = rs.getInt("sage");
                if (rs.wasNull())
                    stu.setSage(null);
                else
                    stu.setSage(sage_res);

                res.add(stu);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return res;
    }

    @Override
    public Student selectBySid(String sid) {
        List<Student> temp = selectAll("select * from student where sid = '" + sid + "'");
        return temp.isEmpty() ? null : temp.get(0);
    }

    @Override
    public List<Student> selectBySname(String str) {
        return selectAll("select * from student where sname like '%" + str + "%' order by length(sid) asc, sid asc");
    }
}
