import { LabelFormatter, ResponsiveBar } from "@nivo/bar";
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
          },
        },
      },
      legends: {
        title: {
          text: {
            fontSize: 55,
          },
        },
      },
    };

    return (
      <div style={{ height: "500px" }}>
        <ResponsiveBar
          data={data}
          keys={["weight"]}
          indexBy="day"
          borderWidth={1.5}
          borderColor={"#000"}
          margin={{ top: 50, right: 130, bottom: 50, left: 60 }}
          padding={0.3}
          valueScale={{ type: "linear" }}
          colors={colors.mySecondaryColor}
          animate={true}
          theme={theme}
          enableLabel
          axisLeft={{
            tickSize: 5,
            tickPadding: 5,
            tickRotation: 0,
            legend: "Desperdício (em kg)",
            legendPosition: "middle",
            legendOffset: -50,
          }}
          axisBottom={{
            legend: "Dias da Semana",
            legendPosition: "middle",
            // tickRotation: 42,
            legendOffset: 45,
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
