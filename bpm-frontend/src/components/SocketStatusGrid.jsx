import React from "react";
import { Card, CardContent, Typography, Chip } from "@mui/material";
import CheckCircleIcon from "@mui/icons-material/CheckCircle";
import ErrorIcon from "@mui/icons-material/Error";
import HourglassEmptyIcon from "@mui/icons-material/HourglassEmpty";
import RadioButtonUncheckedIcon from "@mui/icons-material/RadioButtonUnchecked";

const statusMap = {
  0: { label: "IDLE", color: "default", icon: <RadioButtonUncheckedIcon /> },
  1: { label: "ACTIVE", color: "info", icon: <HourglassEmptyIcon /> },
  2: { label: "PASSED", color: "success", icon: <CheckCircleIcon /> },
  3: { label: "FAILED", color: "error", icon: <ErrorIcon /> },
};

export default function SocketStatusGrid({ sockets }) {
  return (
    <div style={{ display: "flex", flexWrap: "wrap", gap: 16, justifyContent: "center" }}>
      {sockets.map(socket => {
        const status = statusMap[socket.status];
        return (
          <Card key={socket.id} sx={{ width: 140, textAlign: "center" }}>
            <CardContent>
              <Typography variant="h6">Socket {socket.id}</Typography>
              <Chip
                icon={status.icon}
                label={status.label}
                color={status.color}
                variant="outlined"
                sx={{ mt: 1, fontWeight: "bold" }}
              />
            </CardContent>
          </Card>
        );
      })}
    </div>
  );
} 