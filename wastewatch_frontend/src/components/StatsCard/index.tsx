import { Card, Statistic, ConfigProvider } from "antd";
import { ArrowUpOutlined, ArrowDownOutlined } from "@ant-design/icons";
import { CardContainer } from "./styled";
import * as colors from "../../styles/colors"

interface StatsContainerProps {
  text: string;
  value: number;
  type?: "weight" | "percentage";
}

export default function StatsContainer({
  text,
  value,
  type = "weight",
}: StatsContainerProps) {
  const makeStatsCard = (value: number, text: string) => {
    const { color, arrowIcon } =
      value > 0
        ? { color: colors.dangerColor, arrowIcon: <ArrowUpOutlined /> }
        : { color: colors.successColor, arrowIcon: <ArrowDownOutlined /> };

    return (
      <CardContainer>
        <Card className="custom-card" bordered={false}>
          <ConfigProvider
            theme={{
              components: {
                Statistic: {
                  titleFontSize: 18,
                  contentFontSize: 50,
                },
              },
            }}
          >
            <Statistic
              title={text}
              value={Math.abs(value)}
              precision={2}
              prefix={type === "weight" ? "" : arrowIcon}
              decimalSeparator={","}
              groupSeparator={"."}
              suffix={type === "weight" ? "Kg" : "%"}
              valueStyle={{color: type === "weight" ? colors.tertiaryColor : color} }
            />
          </ConfigProvider>
        </Card>
      </CardContainer>
    );
  };

  return <div>{makeStatsCard(value, text)}</div>;
}
