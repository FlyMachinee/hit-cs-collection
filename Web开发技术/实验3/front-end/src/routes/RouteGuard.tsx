import { Navigate, useLocation } from "react-router-dom";

interface IProps {
  children: React.ReactElement<any, any> | null;
}

const RouteGuard: React.FC<IProps> = ({ children }) => {
  const WhiteList = ["/", "/login"];
  const { pathname } = useLocation();
  if (WhiteList.includes(pathname)) {
    return children;
  } else {
    let token = sessionStorage.getItem("username");
    if (token !== null && token !== "") {
      return children;
    } else {
      return <Navigate to="/login" />;
    }
  }
};

export default RouteGuard;
