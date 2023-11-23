import styled from "styled-components";
import * as colors from "../../styles/colors";

export const HeaderContainer = styled.div`
  padding-top: 20px;
  height: 128px;
  text-align: center;
  line-height: 45px;

  h1,
  h2 {
    font-size: 3em;
    font-weight: bolder;
    color: ${colors.myPrimaryColor};
  }
  h2 {
    font-size: 2em;
  }
`;

export const ContentContainer = styled.div`
  min-height: 600px;
  margin: 25px 20px;
  padding: 30px 50px;

  display: flex;
  justify-content: space-around;
`;

export const SpacedDiv = styled.div`
  height: 100%;
  display: flex;
  flex-direction: column;
  justify-content: space-between;
`;

export const Footer = styled.div`
  width: 100%;
  padding: 10px;
  margin-bottom: 20px;
  position: relative;
  bottom: 0;

  display: flex;
  justify-content: center;
  align-items: center;
`;
