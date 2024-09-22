package cn.edu.hit.dao;

import cn.edu.hit.entity.User;

public interface UsersDao {
    /**
     * 用户注册
     * @param user 注册的用户
     * @return 插入状态，插入成功为True
     */
    Boolean insert(User user);

    /**
     * 查询给定的用户是否存在且密码正确
     * @param user 登陆的用户
     * @return 查询结果，正确则返回True
     */
    Boolean isMatch(User user);

    /**
     * 查询给定的用户是否存在
     * @param username 登陆的用户名
     * @return 查询结果，存在则返回True
     */
    Boolean isExist(String username);
}
