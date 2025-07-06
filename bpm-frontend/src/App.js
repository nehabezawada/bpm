import React, { useEffect, useState } from "react";
import JobControlPanel from "./components/JobControlPanel";
import SocketStatusGrid from "./components/SocketStatusGrid";
import JobMetrics from "./components/JobMetrics";
import Notifications from "./components/Notifications";
import RobotWorkflowPanel from "./components/RobotWorkflowPanel";
import { getSockets, getJobStatus } from "./api/bpmApi";

function App() {
  const [sockets, setSockets] = useState([]);
  const [jobStatus, setJobStatus] = useState({});
  const [notification, setNotification] = useState(null);

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
      <JobControlPanel setNotification={setNotification} jobStatus={jobStatus} />
      <JobMetrics jobStatus={jobStatus} />
      <SocketStatusGrid sockets={sockets} setNotification={setNotification} />
      <RobotWorkflowPanel setNotification={setNotification} sockets={sockets} />
      <Notifications message={notification} />
    </div>
  );
}

export default App;
