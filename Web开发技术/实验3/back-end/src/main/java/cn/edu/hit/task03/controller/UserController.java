package cn.edu.hit.task03.controller;

import cn.edu.hit.task03.entity.User;
import cn.edu.hit.task03.service.UserService;
import cn.edu.hit.task03.util.Result;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/user")
@CrossOrigin
public class UserController {

    @Autowired
    private UserService userService;

    @PostMapping("/login")
    public Result login(@RequestBody User user) {
        if (userService.login(user.getUsername(), user.getPassword()) > 0) {
            return Result.ok("OK");
        } else {
            return Result.failed("用户名或密码错误！");
        }
    }
}
