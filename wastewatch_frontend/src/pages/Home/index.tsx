import React, { useEffect, useState } from "react";
import { Row, Col } from "antd";
import { toast } from "react-toastify";

import BarChart from "../../components/BarChart";
import StatsCard from "../../components/StatsCard";
import ImageLink from "../../components/ImageLink";
import { AverageWeightPerDay, WasteData } from "../../types/common_types";
import {
  averageByDay,
  getTotalWeightToInterval,
} from "../../utils/aggregators";
import { HeaderContainer, SpacedDiv, ContentContainer, Footer } from "./styled";
import { getDevices, getDeviceData, getAccessToken } from "../../api/konkerApi";

interface HomeProps {
  restaurant?: string;
  meal?: string;
}

export default function Home({ restaurant = "rs", meal = "all" }: HomeProps) {
  const [data, setData] = useState<WasteData[]>([]);
  const [wasteData, setWasteData] = useState<WasteData[]>([]);
  const [chartData, setChartData] = useState<AverageWeightPerDay[]>([]);

  const restaurantName = {
    ra: "Restaurante Administrativo",
    rs: "Restaurante da Saturnino",
    ru: "Restaurante Universitário",
  }[restaurant];
  const mealName = {
    breakfast: "Café da Manhã",
    lunch: "Almoço",
    dinner: "Jantar",
  }[meal];
  const title =
    !!meal && meal !== "all"
      ? `${restaurantName} - ${mealName}`
      : `${restaurantName}`;
  const wastewatchLogo = require("../../assets/images/wastewatch_logo.png");

  const todayDate = new Date();
  const todayStart = new Date(todayDate);
  todayStart.setHours(0, 0, 0, 0);

  const todayEnd = new Date(todayDate);
  todayEnd.setHours(23, 59, 59, 999);

  useEffect(() => {
    const getWasteData = async () => {
      try {
        await getAccessToken();
        const deviceGuid = await getDevices(process.env.REACT_APP_DEVICE_NAME);
        const statsResponse = await getDeviceData(
          deviceGuid.guid,
          process.env.REACT_APP_CHANNEL_NAME || "",
          new Date("2023-05-11T21:23:58.970Z")
        );
        statsResponse && setWasteData(statsResponse.data.result);
      } catch {
        toast.error("Erro ao recuperar dados de desperdício.");
      }
    };
    getWasteData();

    // TODO: Remove mock data and use konker date to timestamp
    setData([
      {
        timestamp: new Date("2023-11-19T12:30:45.567Z"),
        ingestedTimestamp: new Date("2023-11-19T12:30:45.567Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 398.8996144639814,
        },
      },
      {
        timestamp: new Date("2023-11-20T08:15:30.987Z"),
        ingestedTimestamp: new Date("2023-11-20T08:15:30.987Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 457.35233994279645,
        },
      },
      {
        timestamp: new Date("2023-11-21T14:40:10.123Z"),
        ingestedTimestamp: new Date("2023-11-21T14:40:10.123Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 643.7118996192374,
        },
      },
      {
        timestamp: new Date("2023-11-22T10:20:55.789Z"),
        ingestedTimestamp: new Date("2023-11-22T10:20:55.789Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 351.50619276860306,
        },
      },
      {
        timestamp: new Date("2023-11-23T16:55:40.234Z"),
        ingestedTimestamp: new Date("2023-11-23T16:55:40.234Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 472.72519364609235,
        },
      },
      {
        timestamp: new Date("2023-11-24T13:10:20.567Z"),
        ingestedTimestamp: new Date("2023-11-24T13:10:20.567Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 382.3079994493633,
        },
      },
      {
        timestamp: new Date("2023-11-25T09:45:05.901Z"),
        ingestedTimestamp: new Date("2023-11-25T09:45:05.901Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 623.7576141625484,
        },
      },
      {
        timestamp: new Date("2023-11-19T12:32:15.456Z"),
        ingestedTimestamp: new Date("2023-11-19T12:32:15.456Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 366.67667596329466,
        },
      },
      {
        timestamp: new Date("2023-11-20T08:17:40.789Z"),
        ingestedTimestamp: new Date("2023-11-20T08:17:40.789Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 470.46175974979826,
        },
      },
      {
        timestamp: new Date("2023-11-21T14:42:30.123Z"),
        ingestedTimestamp: new Date("2023-11-21T14:42:30.123Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 593.4835952801852,
        },
      },
      {
        timestamp: new Date("2023-11-22T10:23:55.789Z"),
        ingestedTimestamp: new Date("2023-11-22T10:23:55.789Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 381.6729440009729,
        },
      },
      {
        timestamp: new Date("2023-11-24T13:12:05.567Z"),
        ingestedTimestamp: new Date("2023-11-24T13:12:05.567Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 557.7376575505111,
        },
      },
      {
        timestamp: new Date("2023-11-25T09:47:40.901Z"),
        ingestedTimestamp: new Date("2023-11-25T09:47:40.901Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 457.3134518626907,
        },
      },
      {
        timestamp: new Date("2023-11-19T12:34:30.456Z"),
        ingestedTimestamp: new Date("2023-11-19T12:34:30.456Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 493.522331580776,
        },
      },
      {
        timestamp: new Date("2023-11-20T08:20:55.789Z"),
        ingestedTimestamp: new Date("2023-11-20T08:20:55.789Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 622.5024423710984,
        },
      },
      {
        timestamp: new Date("2023-11-21T14:45:20.123Z"),
        ingestedTimestamp: new Date("2023-11-21T14:45:20.123Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 508.4251286546521,
        },
      },
      {
        timestamp: new Date("2023-11-22T10:26:45.789Z"),
        ingestedTimestamp: new Date("2023-11-22T10:26:45.789Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 477.28820005641694,
        },
      },
      {
        timestamp: new Date("2023-11-23T17:00:10.234Z"),
        ingestedTimestamp: new Date("2023-11-23T17:00:10.234Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 427.3081049031773,
        },
      },
      {
        timestamp: new Date("2023-11-24T13:14:35.567Z"),
        ingestedTimestamp: new Date("2023-11-24T13:14:35.567Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 560.748950008573,
        },
      },
      {
        timestamp: new Date("2023-11-25T09:50:05.901Z"),
        ingestedTimestamp: new Date("2023-11-25T09:50:05.901Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 531.4519820093537,
        },
      },
      {
        timestamp: new Date("2023-11-19T12:36:00.456Z"),
        ingestedTimestamp: new Date("2023-11-19T12:36:00.456Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 507.1074658547466,
        },
      },
      {
        timestamp: new Date("2023-11-20T08:23:25.789Z"),
        ingestedTimestamp: new Date("2023-11-20T08:23:25.789Z"),
        incoming: {
          deviceGuid: "8cad129a-0273-4ae5-8dd0-609e49418466",
          channel: "rs",
        },
        payload: {
          deviceId: "wastewatch-node",
          metric: "Peso",
          value: 636.6636392022565,
        },
      },
    ]);
  }, []);
  console.log("wasteData from konker: ", wasteData);

  useEffect(() => {
    setChartData(averageByDay(data));
  }, [data]);

  return (
    <SpacedDiv>
      <HeaderContainer>
        <a
          href="/"
          target="_blank"
          rel="noreferrer"
          style={{ position: "absolute" }}
        >
          <img src={wastewatchLogo} alt="Logo WasteWatch" />
        </a>
        <h1>{title}</h1>
      </HeaderContainer>
      <ContentContainer>
        <Row gutter={[32, 32]}>
          <Col span={18}>
            <BarChart chartData={chartData} />
          </Col>
          <Col span={5}>
            <SpacedDiv>
              <StatsCard
                text={"Desperdiçado hoje"}
                value={getTotalWeightToInterval(data, todayStart, todayEnd)}
              />
              <StatsCard
                text={"Comparação com a média do mês"}
                value={1.55}
                type="percentage"
              />
              <StatsCard
                text={"Total desperdiçado na semana"}
                value={2815.32}
              />
            </SpacedDiv>
          </Col>
        </Row>
      </ContentContainer>
      <Footer>
        <ImageLink
          imageName="smart-campus.png"
          altText="Logo Smart Campus Unicamp"
          link="https://smartcampus.prefeitura.unicamp.br/"
        />
        <ImageLink
          imageName="ic.png"
          altText="Logo Instituto de Computação da Unicamp"
          link="http://www.ic.unicamp.br/"
        />
        <ImageLink
          imageName="prefeitura.png"
          altText="Logo Prefeitura Universitária Unicamp"
          link="http://www.prefeitura.unicamp.br/"
        />
        <ImageLink
          imageName="konker.png"
          altText="Logo Konker IoT"
          link="http://konkerlabs.com/"
        />
      </Footer>
    </SpacedDiv>
  );
}
