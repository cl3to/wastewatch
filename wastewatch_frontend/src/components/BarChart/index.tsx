import { ResponsiveBar } from "@nivo/bar";
import { Card, Empty } from "antd";
import { AverageWeightPerDay } from "../../types/common_types";

import * as colors from "../../styles/colors";

interface BarChartProps {
  chartData: AverageWeightPerDay[];
}

const BarChart: React.FC<BarChartProps> = ({ chartData }) => {
  // TODO: add type to data
  const buildBarChart = (data: any) => {
    if (!data || data.length === 0)
      return (
        <div
          style={{
            display: "flex",
            alignItems: "center",
            justifyContent: "center",
          }}
        >
          <Empty />
        </div>
      );

    const theme = {
      axis: {
        ticks: {
          text: {
            fontSize: 20,
            fill: "#696773"
          },
        },
        legend: {
            text: {
              fontSize: 24,
              fill: "#272727"
          },
        },
      },
    };

    return (
      <div style={{ height: "500px" }}>
        <ResponsiveBar
          data={data}
          keys={["Desperdicio"]}
          indexBy="day"
          borderWidth={0.5}
          borderColor={"#000"}
          margin={{ top: 20, right: 40, bottom: 60, left: 80 }}
          padding={0.3}
          colors={colors.secondaryColor}
          animate={true}
          theme={theme}
          enableLabel={false}
          axisLeft={{
            tickSize: 5,
            tickPadding: 5,
            tickRotation: 0,
            legend: "Desperdício (em kg)",
            legendPosition: "middle",
            legendOffset: -70,
          }}
          axisBottom={{
            legend: "Dias da Semana",
            legendPosition: "middle",
            legendOffset: 50,
          }}
        />
      </div>
    );
  };
  return (
    <Card className="custom-card" bordered={false}>
      {buildBarChart(chartData)}
    </Card>
  );
};

export default BarChart;
