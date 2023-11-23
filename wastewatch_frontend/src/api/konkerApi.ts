import axios from "../services/axios";
import * as querystring from "querystring";
import { toast } from "react-toastify";

// TODO: add type to functions
// TODO: handle requests error status
export async function getAccessToken() {
  const requestData = {
    grant_type: "client_credentials",
    client_id: process.env.REACT_APP_KONKER_USER,
    client_secret: process.env.REACT_APP_KONKER_PASSWORD,
  };

  const config = {
    headers: {
      "Content-Type": "application/x-www-form-urlencoded",
    },
  };
  try {
    const authResponse = await axios.post(
      "/v1/oauth/token",
      querystring.stringify(requestData),
      config
    );
    const accessToken = authResponse.data.access_token;

    if (!accessToken) {
      throw new Error("Erro ao obter o token de acesso");
    }

    axios.defaults.headers.Authorization = `Bearer ${accessToken}`;
    return accessToken;
  } catch (err) {
    toast.error("Erro ao autenticar a konker");
  }
}

export async function getDevices(deviceName?: String) {
  try {
    // `default` is the default application, this can change in the future
    const devices = await axios.get("/v1/default/devices/");
    if (deviceName) {
      return devices.data.result.find((dev: any) => dev.name === deviceName);
    }
    return devices;
  } catch (err) {
    toast.error("Erro ao recuperar dispositivo.");
  }
}

export async function getDeviceData(
  deviceGuid: string,
  channel: string,
  startDate: Date,
  endDate?: Date,
  pageSize: number = 1000
) {
  try {
    const formattedDate = startDate.toISOString();

    const queryParams = {
      q: `device:${deviceGuid} channel:${channel} timestamp:>${formattedDate}`,
      sort: "oldest",
      limit: pageSize,
    };
    // `default` is the default application, this can change in the future
    const statsResponse = await axios.get("/v1/default/incomingEvents", {
      params: queryParams,
    });

    return statsResponse;
  } catch (err) {
    toast.error("Erro ao recuperar dados do dispositivo.");
  }
}


// OLD CODE
// // #TODO:  add type for functions
// export async function getAccessToken() {
//   const requestData = {
//     grant_type: "client_credentials",
//     client_id: process.env.REACT_APP_KONKER_USER,
//     client_secret: process.env.REACT_APP_KONKER_PASSWORD,
//   };
//   const config = {
//     headers: {
//       "Content-Type": "application/x-www-form-urlencoded",
//     },
//   };
//   //TODO: Add try catch

//   const authResponse = await axios.post(
//     "/v1/oauth/token",
//     querystring.stringify(requestData),
//     config
//   );
//   // TODO: Check a better way to make
//   console.log("Konker accessToken:", authResponse);
//   if (authResponse.data.access_token) {
//     axios.defaults.headers.Authorization = `Bearer ${authResponse.data.access_token}`;
//   }
//   return authResponse.data.access_token;
// }

// export async function getDevices(deviceName?:String) {
//   //TODO: Add try catch
//   // `default` is the default application, this can change in the future
//   const devices = await axios.get("/v1/default/devices/");
//   if(deviceName){
//     return devices.data.result.find(
//       (dev: any) => dev.name === deviceName
//     ); 
//   }
//   return devices
// }

// export async function getDeviceData(deviceGuid: String, channel:string, startDate: Date, endDate?: Date) {
//   // const dtStart = new Date("2023-05-11T21:23:58.970Z");
//   const formattedDate = startDate.toISOString();
//   //TODO: Add try catch
//   // `default` is the default application, this can change in the future
//   const statsResponse = await axios.get(
//     `/v1/default/incomingEvents?q=device:${deviceGuid} channel:${channel} timestamp:>${formattedDate}&sort=oldest&limit=10000`
//   );
//   return statsResponse;
// }
