import styled from "styled-components";
import * as colors from "../../styles/colors";

export const HeaderContainer = styled.div`
  width: 100%;
  height: 128px;
  line-height: 45px;
  
  h1 {
    padding-top: 50px;
    text-align: center;
    font-size: 3em;
    font-weight: bolder;
    color: ${colors.primaryColor};
  }

  a{
    margin-left: 20px;
    padding-top: 20px;
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
