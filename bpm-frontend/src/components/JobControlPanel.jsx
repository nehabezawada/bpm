import React, { useState } from "react";
import { startJob, stopJob, pauseJob, resumeJob } from "../api/bpmApi";

export default function JobControlPanel({ setNotification, jobStatus }) {
  const [quantity, setQuantity] = useState("");

  const handleStart = async () => {
    try {
      await startJob(Number(quantity));
      setNotification("Job started!");
    } catch {
      setNotification("Failed to start job.");
    }
  };

  const handleStop = async () => {
    try {
      const result = await stopJob();
      setNotification(`Job stopped! Response: ${result}`);
    } catch (error) {
      setNotification(`Failed to stop job. Error: ${error.message}`);
    }
  };

  const handlePause = async () => {
    try {
      const result = await pauseJob();
      setNotification(`Job paused! Response: ${result}`);
    } catch (error) {
      setNotification(`Failed to pause job. Error: ${error.message}`);
    }
  };

  const handleResume = async () => {
    try {
      const result = await resumeJob();
      setNotification(`Job resumed! Response: ${result}`);
    } catch (error) {
      setNotification(`Failed to resume job. Error: ${error.message}`);
    }
  };

  return (
    <div className="job-controls">
      <input
        type="number"
        placeholder="Quantity"
        value={quantity}
        onChange={e => setQuantity(e.target.value)}
        disabled={jobStatus?.status === 1}
      />
      <button onClick={handleStart} disabled={jobStatus?.status === 1}>Start</button>
      <button onClick={handleStop}>Stop</button>
      <button onClick={handlePause}>Pause</button>
      <button onClick={handleResume}>Resume</button>
    </div>
  );
} 