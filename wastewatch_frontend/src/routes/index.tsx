import React from "react";
import { BrowserRouter as Router, Routes, Route } from "react-router-dom";

import Home from "../pages/Home";
import NotFound from "../pages/NotFound";

const VALID_RESTAURANTS = ["ra", "rs", "ru"];
const VALID_MEALS = ["breakfast", "lunch", "dinner", ""];

export default function RestaurantRouters() {
  return (
    <Router>
      <Routes>
        {VALID_RESTAURANTS.map((restaurant) =>
          VALID_MEALS.map((meal) => (
            <Route
              path={`/${restaurant}/${meal}`}
              element={<Home restaurant={restaurant} meal={meal} />}
            />
          ))
        )}
        <Route path="/" element={<Home restaurant={"rs"} />} />
        <Route path="*" element={<NotFound />} />
      </Routes>
    </Router>
  );
}
