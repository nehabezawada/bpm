import React, { useEffect, useState } from "react";
import JobControlPanel from "./components/JobControlPanel";
import SocketStatusGrid from "./components/SocketStatusGrid";
import JobMetrics from "./components/JobMetrics";
import Notifications from "./components/Notifications";
import RobotWorkflowPanel from "./components/RobotWorkflowPanel";
import { getSockets, getJobStatus } from "./api/bpmApi";
import { ToastContainer, toast } from "react-toastify";
import "react-toastify/dist/ReactToastify.css";

function App() {
  const [sockets, setSockets] = useState([]);
  const [jobStatus, setJobStatus] = useState({});

  // Polling for real-time updates
  useEffect(() => {
    const fetchData = () => {
      getSockets().then(data => setSockets(data.sockets || []));
      getJobStatus().then(setJobStatus);
    };
    fetchData();
    const interval = setInterval(fetchData, 2000);
    return () => clearInterval(interval);
  }, []);

  return (
    <div className="App">
      <h1>BPM Programming Dashboard</h1>
      <JobControlPanel setNotification={toast} jobStatus={jobStatus} />
      <JobMetrics jobStatus={jobStatus} />
      <SocketStatusGrid sockets={sockets} setNotification={toast} />
      <RobotWorkflowPanel setNotification={toast} sockets={sockets} />
      <ToastContainer position="bottom-right" />
    </div>
  );
}

export default App;
