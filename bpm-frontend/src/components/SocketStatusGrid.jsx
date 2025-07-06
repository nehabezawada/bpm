import React from "react";

const statusClass = {
  0: "idle", // IDLE
  1: "active", // ACTIVE
  2: "passed", // COMPLETED_PASSED
  3: "failed", // COMPLETED_FAILED
};

const statusLabel = {
  0: "IDLE",
  1: "ACTIVE",
  2: "PASSED",
  3: "FAILED",
};

export default function SocketStatusGrid({ sockets }) {
  return (
    <div className="socket-grid">
      {sockets.map(socket => (
        <div
          key={socket.id}
          className={`socket-card ${statusClass[socket.status]}`}
        >
          <div style={{ fontWeight: 700 }}>Socket {socket.id}</div>
          <div style={{ fontSize: "0.95rem", marginTop: 6 }}>{statusLabel[socket.status]}</div>
        </div>
      ))}
    </div>
  );
} 