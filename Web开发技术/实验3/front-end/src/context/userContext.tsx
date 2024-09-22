import { Dispatch, createContext, useReducer } from "react";

export const CurrentUserContext = createContext<string>("");
export const CurrentUserDispatchContext = createContext<Dispatch<UserAction>>(
  () => null
);

export interface UserAction {
  type: "login" | "logout";
  username: string;
}

interface IProps {
  children?: React.ReactNode;
}

export const UserProvider: React.FC<IProps> = ({ children }) => {
  const [currentUser, dispatch] = useReducer(currentUserReducer, "");
  return (
    <CurrentUserContext.Provider value={currentUser}>
      <CurrentUserDispatchContext.Provider value={dispatch}>
        {children}
      </CurrentUserDispatchContext.Provider>
    </CurrentUserContext.Provider>
  );
};

const currentUserReducer = (currentUser: string, action: UserAction) => {
  const { type, username } = action;
  switch (type) {
    case "login":
      return username;
    case "logout":
      return "";
    default:
      return currentUser;
  }
};
