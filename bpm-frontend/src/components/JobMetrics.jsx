import React from "react";

export default function JobMetrics({ jobStatus }) {
  return (
    <div>
      <p>Job Progress: {jobStatus?.completed}/{jobStatus?.quantity}</p>
      <p>Passed: {jobStatus?.passed} | Failed: {jobStatus?.failed}</p>
    </div>
  );
} 