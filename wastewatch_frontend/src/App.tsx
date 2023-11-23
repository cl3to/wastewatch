import React from "react";

import GlobalStyle from "./styles/GlobalStyles";
import RestaurantRouters from "./routes";

function App() {
  return (
    <>
      <RestaurantRouters />
      <GlobalStyle />
    </>
  );
}

export default App;
