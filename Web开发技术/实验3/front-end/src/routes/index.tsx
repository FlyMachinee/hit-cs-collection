import { Navigate, createBrowserRouter } from "react-router-dom";
import { ReactNode } from "react";
import Main from "@/views/Main/index";
import Login from "@/views/Login/index";
import Root from "@/views/Root";
import { UserProvider } from "@/context/userContext";
import RouteGuard from "./RouteGuard";

interface Route {
  path: string;
  name?: string;
  element: ReactNode;
  children?: Route[];
}

const routes: Route[] = [
  {
    path: "/",
    element: <Navigate to="/login" />,
  },
  {
    path: "/",
    name: "root",
    element: (
      <RouteGuard>
        <UserProvider>
          <Root />
        </UserProvider>
      </RouteGuard>
    ),
    children: [
      {
        path: "main",
        name: "main",
        element: <Main />,
      },
      {
        path: "login",
        name: "login",
        element: <Login />,
      },
    ],
  },
];

export const router = createBrowserRouter(routes);
