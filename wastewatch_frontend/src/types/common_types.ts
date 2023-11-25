// export interface WasteData {
//   restaurant: string;
//   weight: number;
//   date: Date;
// }

export interface WasteDataPayload {
  deviceId: string;
  metric: string;
  value: number;
}
export interface WasteData {
  timestamp: Date;
  ingestedTimestamp: Date;
  incoming: {
    deviceGuid: string;
    channel: string;
  };
  payload: WasteDataPayload;
}
export interface AverageWeightPerDay {
  day: string;
  Desperdicio: number;
}
