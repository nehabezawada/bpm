const API_BASE = "/api";

export const startJob = (quantity) =>
  fetch(`${API_BASE}/job/start`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ quantity }),
  }).then(res => res.json());

export const stopJob = () =>
  fetch(`${API_BASE}/job/stop`, { method: "POST" }).then(res => res.text());

export const pauseJob = () =>
  fetch(`${API_BASE}/job/pause`, { method: "POST" }).then(res => res.text());

export const resumeJob = () =>
  fetch(`${API_BASE}/job/resume`, { method: "POST" }).then(res => res.text());

export const getSockets = () =>
  fetch(`${API_BASE}/programming/sockets`).then(res => res.json());

export const getJobStatus = () =>
  fetch(`${API_BASE}/job/status`).then(res => res.json());

export const getReadyToPlace = () =>
  fetch(`${API_BASE}/robot/ready-to-place`).then(res => res.json());

export const getReadyToPick = () =>
  fetch(`${API_BASE}/robot/ready-to-pick`).then(res => res.json());

export const devicePlaced = (socketId) =>
  fetch(`${API_BASE}/robot/device-placed`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ id: socketId }),
  }).then(res => res.text());

export const devicePicked = (socketId) =>
  fetch(`${API_BASE}/robot/device-picked`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ id: socketId }),
  }).then(res => res.text());