import React, { useState } from "react";
import { devicePlaced, devicePicked, getReadyToPlace, getReadyToPick } from "../api/bpmApi";

export default function RobotWorkflowPanel({ setNotification, sockets }) {
  const [selectedSocket, setSelectedSocket] = useState(null);

  const handleDevicePlaced = async (socketId) => {
    try {
      const result = await devicePlaced(socketId);
      setNotification(`Device placed on socket ${socketId}! Response: ${result}`);
    } catch (error) {
      setNotification(`Failed to place device on socket ${socketId}. Error: ${error.message}`);
    }
  };

  const handleDevicePicked = async (socketId) => {
    try {
      const result = await devicePicked(socketId);
      setNotification(`Device picked from socket ${socketId}! Response: ${result}`);
    } catch (error) {
      setNotification(`Failed to pick device from socket ${socketId}. Error: ${error.message}`);
    }
  };

  const handleGetReadyToPlace = async () => {
    try {
      const result = await getReadyToPlace();
      setNotification(`Ready to place sockets: ${JSON.stringify(result.sockets)}`);
    } catch (error) {
      setNotification(`Failed to get ready to place sockets. Error: ${error.message}`);
    }
  };

  const handleGetReadyToPick = async () => {
    try {
      const result = await getReadyToPick();
      setNotification(`Ready to pick sockets: ${JSON.stringify(result.sockets)}`);
    } catch (error) {
      setNotification(`Failed to get ready to pick sockets. Error: ${error.message}`);
    }
  };

  return (
    <div className="robot-workflow-panel">
      <h3>🤖 Robot Workflow Testing</h3>
      
      <div className="robot-controls">
        <div className="control-section">
          <h4>Robot Status</h4>
          <button onClick={handleGetReadyToPlace} className="robot-btn">
            Check Ready to Place
          </button>
          <button onClick={handleGetReadyToPick} className="robot-btn">
            Check Ready to Pick
          </button>
        </div>

        <div className="control-section">
          <h4>Manual Robot Operations</h4>
          <div className="socket-selection">
            <label>Select Socket:</label>
            <select 
              value={selectedSocket !== null ? selectedSocket : ""} 
              onChange={(e) => setSelectedSocket(e.target.value !== ""? parseInt(e.target.value) : null)}
            >
              <option value="">Choose a socket...</option>
              {sockets.map(socket => (
                <option key={socket.id} value={socket.id}>
                  Socket {socket.id} ({socket.status === 0 ? 'IDLE' : socket.status === 1 ? 'ACTIVE' : socket.status === 2 ? 'PASSED' : 'FAILED'})
                </option>
              ))}
            </select>
          </div>
          
          <div className="robot-actions">
            <button 
              onClick={() => handleDevicePlaced(selectedSocket)}
              disabled={selectedSocket === null}
              className="robot-btn place-btn"
            >
              🤖 Place Device
            </button>
            <button 
              onClick={() => handleDevicePicked(selectedSocket)}
              disabled={selectedSocket === null}
              className="robot-btn pick-btn"
            >
              🤖 Pick Device
            </button>
          </div>
        </div>
      </div>

      <div className="workflow-info">
        <h4>Workflow Steps:</h4>
        <ol>
          <li>Start a job with quantity</li>
          <li>Check "Ready to Place" - shows IDLE sockets</li>
          <li>Select a socket and click "Place Device"</li>
          <li>Socket should change to PASSED/FAILED status</li>
          <li>Check "Ready to Pick" - shows completed sockets</li>
          <li>Select a completed socket and click "Pick Device"</li>
          <li>Socket should return to IDLE status</li>
        </ol>
      </div>
    </div>
  );
} 