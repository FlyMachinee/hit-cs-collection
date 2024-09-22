package cn.edu.hit.task03.service.impl;

import cn.edu.hit.task03.mapper.UserMapper;
import cn.edu.hit.task03.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class UserServiceImpl implements UserService {

    @Autowired
    private UserMapper userMapper;

    @Override
    public Integer login(String username, String password) {
        return userMapper.login(username, password);
    }
}
