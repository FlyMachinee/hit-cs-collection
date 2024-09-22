import { RouterProvider } from "react-router-dom";
import { ConfigProvider } from "antd";
import { router } from "@/routes/index";
import "./App.css";
import "antd/dist/reset.css";

const App = () => {
  return (
    <ConfigProvider
      theme={{
        token: {
          // Seed Token，影响范围大
          colorPrimary: "#4d8ddd",
          borderRadius: 2,

          // 派生变量，影响范围小
          // colorBgContainer: "#f6ffed",
        },
      }}
    >
      <RouterProvider router={router} />
    </ConfigProvider>
  );
};

export default App;
