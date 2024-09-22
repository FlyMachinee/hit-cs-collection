import React, { useContext, useEffect } from "react";
import { Button, Flex, Layout, Space, theme } from "antd";
import { Outlet, useNavigate } from "react-router-dom";
import {
  CurrentUserContext,
  CurrentUserDispatchContext,
} from "@/context/userContext";

const { Header, Content, Footer } = Layout;

const Root: React.FC = () => {
  const {
    token: { colorPrimary },
  } = theme.useToken();

  const currentUser = useContext(CurrentUserContext);
  const currentUserDispatch = useContext(CurrentUserDispatchContext);
  const navigate = useNavigate();

  useEffect(() => {
    const storage = sessionStorage.getItem("username");
    if (storage !== null && storage !== "") {
      currentUserDispatch({
        type: "login",
        username: storage,
      });
      navigate("/main");
    }
  }, [currentUserDispatch, navigate]);

  const onLogout = () => {
    sessionStorage.setItem("username", "");
    sessionStorage.removeItem("username");
    currentUserDispatch({
      type: "logout",
      username: "any",
    });
    navigate("/login");
  };

  return (
    <Layout style={{ minHeight: "100%" }}>
      <Header
        style={{
          display: "flex",
          color: "white",
          background: colorPrimary,
        }}
      >
        <Flex justify="space-between" style={{ width: "100%" }}>
          <div style={{ fontSize: "18px" }}>哈尔滨工业大学判官系统</div>
          {currentUser !== "" ? (
            <Space>
              <span>欢迎！{sessionStorage.getItem("username")}</span>
              <Button type="link" style={{ color: "white" }} onClick={onLogout}>
                登出
              </Button>
            </Space>
          ) : (
            <span>欢迎！</span>
          )}
        </Flex>
      </Header>

      <Content
        style={{
          display: "flex",
          padding: "30px",
          paddingBottom: "0",
        }}
      >
        <Outlet />
      </Content>

      <Footer style={{ textAlign: "center", fontSize: "10px" }}>
        哈尔滨工业大学判官系统 ©{new Date().getFullYear()} Create By Fly_Machine
        Using React
      </Footer>
    </Layout>
  );
};

export default Root;
