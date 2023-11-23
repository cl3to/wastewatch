import React, { useEffect, useState } from "react";
import { Row, Col } from "antd";
import { toast } from "react-toastify";

import BarChart from "../../components/BarChart";
import StatsCard from "../../components/StatsCard";
import ImageLink from "../../components/ImageLink";
import { AverageWeightPerDay, WasteData } from "../../types/common_types";
import { averageByDay } from "../../utils/aggregators";
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
  const subTitle =
    !!meal && meal !== "all"
      ? `${restaurantName} - ${mealName}`
      : `${restaurantName}`;

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
        restaurant: "ru",
        weight: 145.72,
        date: new Date("2023-11-19T07:45:00Z"),
      },
      {
        restaurant: "ru",
        weight: 145.72,
        date: new Date("2016-07-30T07:45:00Z"),
      },
      {
        restaurant: "ra",
        weight: 203.45,
        date: new Date("2016-08-03T07:45:00Z"),
      },
      {
        restaurant: "rs",
        weight: 97.88,
        date: new Date("2016-08-11T07:45:00Z"),
      },
      {
        restaurant: "ru",
        weight: 112.33,
        date: new Date("2016-08-17T07:45:00Z"),
      },
      {
        restaurant: "ra",
        weight: 250.11,
        date: new Date("2016-08-14T07:45:00Z"),
      },
      {
        restaurant: "rs",
        weight: 175.64,
        date: new Date("2016-08-30T07:45:00Z"),
      },
      {
        restaurant: "ru",
        weight: 88.2,
        date: new Date("2016-09-02T07:45:00Z"),
      },
      {
        restaurant: "ra",
        weight: 185.76,
        date: new Date("2016-09-10T07:45:00Z"),
      },
      {
        restaurant: "rs",
        weight: 120.98,
        date: new Date("2016-02-21T07:45:00Z"),
      },
      {
        restaurant: "ru",
        weight: 271.05,
        date: new Date("2016-09-22T07:45:00Z"),
      },
      {
        restaurant: "ra",
        weight: 68.77,
        date: new Date("2016-10-02T07:45:00Z"),
      },
      {
        restaurant: "rs",
        weight: 156.42,
        date: new Date("2016-10-19T07:45:00Z"),
      },
      {
        restaurant: "ru",
        weight: 102.88,
        date: new Date("2016-10-19T07:45:00Z"),
      },
      {
        restaurant: "ra",
        weight: 189.2,
        date: new Date("2016-10-01T07:45:00Z"),
      },
      {
        restaurant: "rs",
        weight: 220.75,
        date: new Date("2016-11-14T07:45:00Z"),
      },
      {
        restaurant: "ru",
        weight: 78.46,
        date: new Date("2016-11-09T07:45:00Z"),
      },
      {
        restaurant: "ra",
        weight: 135.6,
        date: new Date("2016-11-16T07:45:00Z"),
      },
      {
        restaurant: "rs",
        weight: 198.33,
        date: new Date("2016-11-23T07:45:00Z"),
      },
      {
        restaurant: "ru",
        weight: 56.89,
        date: new Date("2016-11-30T07:45:00Z"),
      },
      {
        restaurant: "ra",
        weight: 165.75,
        date: new Date("2016-12-07T07:45:00Z"),
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
        <h1> WasteWatch </h1>
        <h2>{subTitle}</h2>
      </HeaderContainer>
      <ContentContainer>
        <Row gutter={[32, 32]}>
          <Col span={18}>
            <BarChart chartData={chartData} />
          </Col>
          <Col span={5}>
            <SpacedDiv>
              <StatsCard text={"Desperdiçado Hoje"} value={142.2} />
              <StatsCard
                text={"Comparação com a média do mês"}
                value={-1.55}
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
