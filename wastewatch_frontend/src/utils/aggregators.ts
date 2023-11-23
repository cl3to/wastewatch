import { AverageWeightPerDay, WasteData } from "../types/common_types";

interface wasteDataByDay {
  [dayOfWeek: string]: WasteData[];
}

export const formatDataPerDay = (data: WasteData[]) => {
  const dataPerDay: wasteDataByDay = {};

  data.forEach((entry) => {
    const date = entry.date;
    const dayOfWeek = date.toLocaleDateString("en-US", { weekday: "long" });

    if (!dataPerDay[dayOfWeek]) {
      dataPerDay[dayOfWeek] = [];
    }
    dataPerDay[dayOfWeek].push(entry);
  });

  return dataPerDay;
};

export const averageByDay = (data: WasteData[]): AverageWeightPerDay[] => {
  const weekDays:{ [key: string]: string } = {
    "Sunday": "Domingo",
    "Monday": "Segunda-feira",
    "Tuesday": "Terça-feira",
    "Wednesday": "Quarta-feira",
    "Thursday": "Quinta-feira",
    "Friday": "Sexta-feira",
    "Saturday": "Sábado",
  };
  if (data.length === 0) return [];
  const dataPerDay = formatDataPerDay(data);
  const averageWeightPerDay: AverageWeightPerDay[] = [];
  for (const day of Object.keys(weekDays)) {
    if (dataPerDay.hasOwnProperty(day)) {
      const totalWeight = dataPerDay[day].reduce(
        (accumulator: number, obj: WasteData) => accumulator + obj.weight,
        0
      );
      averageWeightPerDay.push({
        day: weekDays[day],
        weight: Number((totalWeight / dataPerDay[day].length).toFixed(2)),
      });
    }
  }
  console.log("averageWeightPerDay", averageWeightPerDay)
  return averageWeightPerDay;
};


