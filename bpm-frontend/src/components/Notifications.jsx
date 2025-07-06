import React from "react";
export default function Notifications({ message }) {
  if (!message) return null;
  return <div className="notification">{message}</div>;
} 