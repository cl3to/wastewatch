import React from "react";

interface ImageLinkProps {
  imageName: string;
  altText: string;
  link: string;
}

export default function ImageLink({
  imageName,
  altText,
  link,
}: ImageLinkProps) {
  const image = require("../../assets/images/"+imageName);

  return (
    <a href={link} target="_blank" rel="noreferrer" style={{padding: "0px 50px" }}>
      <img src={image} alt={altText} />
    </a>
  );
}
