import React from "react";

import { NotFoundContainer } from "./styled";

export default function NotFound() {
  const notFoundDino = require("../../assets/images/dino_404.png");

  return (
    <NotFoundContainer>
      <img src={notFoundDino} alt="Página não encontrada" />
      <h1>Página não encontrada</h1>
    </NotFoundContainer>
  );
}
