import { createGlobalStyle } from 'styled-components';
import * as colors from './colors';

export default createGlobalStyle`
  * {
    margin: 0;
    padding: 0;
    outline: none;
    box-sizing: border-box;
  }

  body {
    font-family: sans-serif;
    background: ${colors.myBackgroundColor};
  }

  html, body, #root {
    height: 100%;
  }
`;
