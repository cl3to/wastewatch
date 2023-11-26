import axios from 'axios';

export default axios.create({
  baseURL: process.env.REACT_APP_KONKER_BASE_URL,
});
